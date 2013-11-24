#include "opencash/controller/DocumentController.h"
#include "generated/Account-odb.hxx"
#include "generated/AccountsMeta-odb.hxx"

#include <odb/database.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/session.hxx>

#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

#include <memory>

namespace opencash { namespace controller {

  using namespace odb::core;

  using Account = opencash::model::Account;
  using AccountType = opencash::model::Account::AccountType;
  using AccountPtr = opencash::model::Account::AccountPtr;
  using Accounts = opencash::model::Account::Accounts;
  using AccountsMeta = opencash::model::AccountsMeta;

  DocumentController::DocumentController(
      const std::string & dbFilename,
      bool shouldInitialize
      ) :
    _dbFilename(dbFilename),
    _accountsMeta(new AccountsMeta()),
    _db(new odb::sqlite::database(dbFilename,
          SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE))
  {
    if (shouldInitialize) {
      initializeDocument();
    }
  }

  AccountsMeta * DocumentController::getAccountsMeta() const
  {
    return _accountsMeta.get();
  }

  std::unique_ptr<Accounts> DocumentController::retrieveAccounts() const
  {
    std::unique_ptr<Accounts> ret(new Accounts);

    session s;
    transaction t(_db->begin());
    auto r(_db->query<Account>());
    for (auto i(r.begin()); i != r.end(); ++i)
    {
      ret->push_back(AccountPtr(i.load()));
    }
    t.commit();

    return ret;
  }

  AccountPtr DocumentController::newAccount() const
  {
    Poco::UUIDGenerator & generator = Poco::UUIDGenerator::defaultGenerator();
    Poco::UUID uuid(generator.createOne());
    // TODO: make sure this UUID doesn't exist in DB yet
    return AccountPtr(new Account(uuid.toString()));
  }

  void DocumentController::persistAccount(const Account & account)
  {
    transaction t(_db->begin());
    _db->persist(account);
    t.commit();

    updateAccountsMeta();
  }

  void DocumentController::initializeDocument()
  {
    auto acc = newAccount();
    acc->setName("Root Account");
    acc->setDescription("A pseudo account to represent the root of the account structure");
    acc->setType(AccountType::Root);

    transaction t(_db->begin());
    schema_catalog::create_schema(*_db);
    _db->persist(*acc);
    t.commit();

    updateAccountsMeta();
  }

  void DocumentController::updateAccountsMeta()
  {
    transaction t(_db->begin());
    odb::result<AccountsMeta> r(_db->query<AccountsMeta>());
    r.begin().load(*_accountsMeta);
    t.commit();
  }

} }
