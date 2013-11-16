#include "opencash/controller/DocumentController.h"
#include "generated/Account-odb.hxx"
#include "generated/AccountsMeta-odb.hxx"

#include <odb/database.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>

#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

#include <memory>
#include <iostream>

using namespace odb::core;

using opencash::model::Account;
using opencash::model::AccountsMeta;

using std::string;
using std::unique_ptr;
using std::vector;

namespace opencash { namespace controller {

  DocumentController::DocumentController(
      const string & dbFilename,
      bool shouldInitialize
      ) :
    _dbFilename(dbFilename),
    _accountsMeta(new AccountsMeta()),
    _db(new odb::sqlite::database(dbFilename,
          SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE))
  {
    if (shouldInitialize)
      initializeDocument();
  }

  AccountsMeta * DocumentController::getAccountsMeta() const
  {
    return _accountsMeta.get();
  }

  unique_ptr<vector<unique_ptr<Account>>>
  DocumentController::retrieveAccounts() const
  {
    unique_ptr<vector<unique_ptr<Account>>>
      ret(new vector<unique_ptr<Account>>);

    transaction t(_db->begin());
    auto r(_db->query<Account>());
    for (auto i(r.begin()); i != r.end(); ++i)
    {
      ret->push_back(unique_ptr<Account>(i.load()));
    }
    t.commit();

    return ret;
  }

  unique_ptr<Account> DocumentController::newAccount() const
  {
    Poco::UUIDGenerator & generator = Poco::UUIDGenerator::defaultGenerator();
    Poco::UUID uuid(generator.createOne());
    // TODO: make sure this UUID doesn't exist in DB yet
    return unique_ptr<Account>(new Account(uuid.toString()));
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
    transaction t(_db->begin());
    schema_catalog::create_schema(*_db);
    t.commit();
  }

  void DocumentController::updateAccountsMeta()
  {
    transaction t(_db->begin());
    odb::result<AccountsMeta> r(_db->query<AccountsMeta>());
    r.begin().load(*_accountsMeta);
    t.commit();
  }

} }
