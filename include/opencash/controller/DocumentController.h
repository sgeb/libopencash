#ifndef __OC_CONTROLLER_DOCUMENTCONTROLLER_H_
#define __OC_CONTROLLER_DOCUMENTCONTROLLER_H_

#include <odb/database.hxx>
#include <string>
#include <memory>

namespace opencash { namespace model {
  class Account;
  class AccountsMeta;
}}

using opencash::model::Account;
using opencash::model::AccountsMeta;

using std::string;
using std::unique_ptr;
using std::vector;

namespace opencash { namespace controller {

  class DocumentController {
    public: // general methods
      DocumentController(
          const string & dbFilename,
          bool shouldInitialize = false);

    public: // related to Accounts
      const AccountsMeta * getAccountsMeta() const;
      unique_ptr<vector<unique_ptr<Account>>> retrieveAccounts() const;
      unique_ptr<Account> newAccount() const;
      void persistAccount(const Account & account);

    private: // private methods
      void initializeDocument();
      void updateAccountsMeta();

    private: // private members
      const string _dbFilename;
      unique_ptr<AccountsMeta> _accountsMeta;
      unique_ptr<odb::database> _db;
  };

} }

#endif
