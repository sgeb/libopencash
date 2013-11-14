#ifndef __OC_MODEL_ACCOUNT_H_
#define __OC_MODEL_ACCOUNT_H_

#include "opencash/model/ObservableModel.h"

#include <Poco/UUID.h>
#include <odb/core.hxx>
#include <string>

namespace opencash { namespace model {

  enum class AccountType {
    None,
    Root,
    Asset,
    Liability,
    Expense,
    Income,
    Equity,
  };

  #pragma db object table("accounts")
  class Account : public ObservableModel {
    friend class odb::access;

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


    private:
      Account();

      #pragma db id
      std::string _uuid;

      std::string _name;
      std::string _description;
      AccountType _type;
  };

}}

#endif
