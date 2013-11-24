#ifndef __OC_CONTROLLER_DOCUMENTCONTROLLER_H_
#define __OC_CONTROLLER_DOCUMENTCONTROLLER_H_

#include <odb/database.hxx>
#include <string>
#include <memory>

namespace opencash { namespace model {
  class Account;
  class AccountsMeta;
}}

namespace opencash { namespace controller {

  class DocumentController {
    using Account = opencash::model::Account;
    using AccountsMeta = opencash::model::AccountsMeta;

    public: // general methods
      DocumentController(const std::string & dbFilename,
          bool shouldInitialize = false);

    public: // related to Accounts
      AccountsMeta * getAccountsMeta() const;
      std::unique_ptr<std::vector<std::shared_ptr<Account>>>
        retrieveAccounts() const;
      std::shared_ptr<Account> newAccount() const;
      void persistAccount(const Account & account);

    private: // private methods
      void initializeDocument();
      void updateAccountsMeta();

    private: // private members
      const std::string _dbFilename;
      std::unique_ptr<AccountsMeta> _accountsMeta;
      std::unique_ptr<odb::database> _db;
  };

}}

#endif
