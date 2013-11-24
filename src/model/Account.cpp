#include "opencash/model/Account.h"

#include <sstream>

using std::shared_ptr;
using AccountType = opencash::model::Account::AccountType;

namespace opencash { namespace model {

  Account::Account(const std::string & uuid) : _uuid(uuid) {}
  Account::Account() {}

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
    willChange("name");
    _name = name;
    didChange("name");
  }

  std::string Account::getDescription() const
  {
    return _description;
  }

  void Account::setDescription(std::string description)
  {
    willChange("description");
    _description = description;
    didChange("description");
  }

  AccountType Account::getType() const
  {
    return _type;
  }

  void Account::setType(AccountType type)
  {
    willChange("type");
    _type = type;
    didChange("type");
  }

  shared_ptr<Account> Account::getParent() const
  {
    return _parent;
  }

  void Account::setParent(shared_ptr<Account> parent)
  {
    if (&*parent == &*_parent) { return; }

    using ChangeType = opencash::model::ObservableModel::ChangeType;

    willChange("parent");

    // unregister from previous parent
    if (_parent) {
      auto index = std::numeric_limits<std::size_t>::max();

      auto children = _parent->_children;
      auto child = find_if(children.cbegin(), children.cend(),
          [this](decltype(*children.cbegin()) item) {
            return (&*(item.lock()) == this);
          });
      if (child != children.cend()) {
        index = child - children.cbegin();

        _parent->willChangeAtIndex("children", index, ChangeType::Removal);
        children.erase(child);
        _parent->didChangeAtIndex("children", index, ChangeType::Removal);
      }
    }

    // register with new parent
    if (parent) {
      auto index = parent->_children.size();

      parent->willChangeAtIndex("children", index, ChangeType::Insertion);
      parent->_children.push_back(shared_from_this());
      parent->didChangeAtIndex("children", index, ChangeType::Insertion);
    }

    _parent = parent;
    didChange("parent");
  }

  const std::vector<std::weak_ptr<Account>> & Account::getChildren() const
  {
    return _children;
  }

}}
