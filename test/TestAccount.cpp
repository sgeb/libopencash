#include "opencash/model/Account.h"
#include "opencash/controller/ModelObserver.h"

#include <Poco/Delegate.h>
#include <gtest/gtest.h>

using namespace opencash::model;
using namespace std;

const string A_UUID = "a_uuid";
const string ANOTHER_UUID = "another_uuid";

class TestAccountObserver : public opencash::controller::ModelObserver {
  public:
    TestAccountObserver(Account & account) : ModelObserver(account) {}

    bool hasWillChangeValueBeenFiredForKey(const string & key) const
    {
      return (_keysOfWillChangeValue.find(key) != _keysOfWillChangeValue.end());
    }

    bool hasDidChangeValueBeenFiredForKey(const string & key) const
    {
      return (_keysOfDidChangeValue.find(key) != _keysOfDidChangeValue.end());
    }

  protected: // overrides of ModelObserver
    void willChangeValueForKey(const string & key) override
    {
      _keysOfWillChangeValue.insert(key);
    }

    void didChangeValueForKey(const string & key) override
    {
      _keysOfDidChangeValue.insert(key);
    }

  private:
    multiset<string> _keysOfWillChangeValue;
    multiset<string> _keysOfDidChangeValue;
};

TEST(TestAccount, equalityIsBasedOnUuid) {
  // given
  Account a1(A_UUID);
  a1.setName("a1");

  Account a2(A_UUID);
  a2.setName("a2");

  Account another1(ANOTHER_UUID);
  another1.setName("another1");

  Account another2(ANOTHER_UUID);
  another2.setName("another2");

  // when
  bool a1EqualsA1 = (a1 == a1);
  bool a1EqualsA2 = (a1 == a2);
  bool a1EqualsAnother1 = (a1 == another1);
  bool a1EqualsAnother2 = (a1 == another2);
  bool another1EqualsAnother2 = (another1 == another2);

  // then
  ASSERT_TRUE(a1EqualsA1);
  ASSERT_TRUE(a1EqualsA2);
  ASSERT_FALSE(a1EqualsAnother1);
  ASSERT_FALSE(a1EqualsAnother2);
  ASSERT_TRUE(another1EqualsAnother2);
}

TEST(TestAccount, observerEventsAreTriggered) {
  // given
  Account acc(A_UUID);
  TestAccountObserver obs(acc);

  // when
  acc.setName("A name");
  acc.setDescription("A description");
  acc.setType(AccountType::Asset);

  // then
  ASSERT_TRUE(obs.hasWillChangeValueBeenFiredForKey("name"));
  ASSERT_TRUE(obs.hasDidChangeValueBeenFiredForKey("name"));

  ASSERT_TRUE(obs.hasWillChangeValueBeenFiredForKey("description"));
  ASSERT_TRUE(obs.hasDidChangeValueBeenFiredForKey("description"));

  ASSERT_TRUE(obs.hasWillChangeValueBeenFiredForKey("type"));
  ASSERT_TRUE(obs.hasDidChangeValueBeenFiredForKey("type"));
}
