#ifndef __OC_CONTROLLER_DOCUMENTCONTROLLER_H_
#define __OC_CONTROLLER_DOCUMENTCONTROLLER_H_

#include "opencash/model/Account.h"

#include <odb/database.hxx>
#include <string>
#include <memory>

namespace opencash { namespace model {
  class AccountsMeta;
}}

namespace opencash { namespace controller {

  class DocumentController {
    public: // public using aliases
      using Account = opencash::model::Account;
      using AccountPtr = opencash::model::Account::AccountPtr;
      using Accounts = opencash::model::Account::Accounts;
      using AccountsMeta = opencash::model::AccountsMeta;

    public: // general methods
      DocumentController(const std::string & dbFilename,
          bool shouldInitialize = false);

    public: // related to Accounts
      AccountsMeta * getAccountsMeta() const;
      std::unique_ptr<Accounts> retrieveAccounts() const;
      AccountPtr newAccount() const;
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
