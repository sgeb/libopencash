#ifndef __OC_MODEL_ACCOUNT_H_
#define __OC_MODEL_ACCOUNT_H_

#include "opencash/model/ObservableModel.h"

#include <Poco/UUID.h>
#include <odb/core.hxx>
#include <string>
#include <memory>

namespace opencash { namespace model {


  #pragma db object table("accounts") pointer(std::shared_ptr)
  class Account :
    public ::std::enable_shared_from_this<Account>,
    public ObservableModel
  {
    friend class odb::access;

    public:
      using AccountPtr = std::shared_ptr<Account>;
      using Accounts = std::vector<AccountPtr>;
      using WeakAccounts = std::vector<std::weak_ptr<Account>>;

      enum class AccountType {
        None,
        Root,
        Asset,
        Liability,
        Expense,
        Income,
        Equity,
      };

    public:
      Account(const std::string & uuid);
      bool operator==(const Account & rhs) const;

      std::string getUuid() const;

      std::string getName() const;
      void setName(std::string name);

      std::string getDescr() const;
      void setDescr(std::string descr);

      AccountType getType() const;
      void setType(AccountType type);

      AccountPtr getParent() const;
      void setParent(AccountPtr parent);

      const WeakAccounts & getChildren() const;

    private:
      Account();

      #pragma db id
      std::string _uuid;

      #pragma db set(setName)
      std::string _name;

      #pragma db set(setDescr)
      std::string _descr;

      #pragma db set(setType)
      AccountType _type;

      #pragma db set(setParent)
      AccountPtr _parent;

      #pragma db value_not_null inverse(_parent)
      WeakAccounts _children;
  };

}}

#endif
