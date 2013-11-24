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

      std::string getDescription() const;
      void setDescription(std::string description);

      AccountType getType() const;
      void setType(AccountType type);

      std::shared_ptr<Account> getParent() const;
      void setParent(std::shared_ptr<Account> parent);

      const std::vector<std::weak_ptr<Account>> & getChildren() const;

    private:
      Account();

      #pragma db id
      std::string _uuid;

      #pragma db set(setName)
      std::string _name;

      #pragma db set(setDescription)
      std::string _description;

      #pragma db set(setType)
      AccountType _type;

      #pragma db set(setParent)
      std::shared_ptr<Account> _parent;

      #pragma db value_not_null inverse(_parent)
      std::vector<std::weak_ptr<Account>> _children;
  };

}}

#endif
