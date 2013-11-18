#include "opencash/model/Account.h"

#include <sstream>

using std::shared_ptr;

namespace opencash { namespace model {

  Account::Account(const std::string & uuid)
    : _uuid(uuid)
  {
  }

  Account::Account()
  {
  }

  bool Account::operator==(const Account & rhs) const
  {
    return (this == &rhs) || (this->_uuid == rhs._uuid);
  }

  std::string Account::getUuid() const
  {
    return _uuid;
  }

  std::string Account::getName() const
  {
    return _name;
  }

  void Account::setName(std::string name)
  {
    willChangeValueForKey("name");
    _name = name;
    didChangeValueForKey("name");
  }

  std::string Account::getDescription() const
  {
    return _description;
  }

  void Account::setDescription(std::string description)
  {
    willChangeValueForKey("description");
    _description = description;
    didChangeValueForKey("description");
  }

  AccountType Account::getType() const
  {
    return _type;
  }

  void Account::setType(AccountType type)
  {
    willChangeValueForKey("type");
    _type = type;
    didChangeValueForKey("type");
  }

  shared_ptr<Account> Account::getParent() const
  {
    return _parent;
  }

  void Account::setParent(shared_ptr<Account> parent)
  {
    if (parent) {
      auto thisPtr = shared_from_this();
      parent->_children.push_back(thisPtr);
    }

    willChangeValueForKey("parent");
    _parent = parent;
    didChangeValueForKey("parent");
  }

  const vector<weak_ptr<Account>> & Account::getChildren() const
  {
    return _children;
  }

}}
