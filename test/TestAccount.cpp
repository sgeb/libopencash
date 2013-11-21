#include "opencash/model/Account.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace opencash::model;
using namespace std;
using namespace ::testing;

const string A_UUID = "a_uuid";
const string ANOTHER_UUID = "another_uuid";
const string YET_ANOTHER_UUID = "yet_another_uuid";

TEST(TestAccount, shouldAllowOneParent) {
  // given
  auto parentAcc = make_shared<Account>(A_UUID);
  parentAcc->setName("parent");

  auto childAcc = make_shared<Account>(ANOTHER_UUID);
  childAcc->setName("child");

  // when
  childAcc->setParent(parentAcc);

  // then
  ASSERT_EQ(*parentAcc, *childAcc->getParent());
}

TEST(TestAccount, shouldAllowMultipleChildren) {
  // given
  auto parentAcc = make_shared<Account>(A_UUID);
  parentAcc->setName("parent");

  auto childAcc1 = make_shared<Account>(ANOTHER_UUID);
  childAcc1->setName("child1");

  auto childAcc2 = make_shared<Account>(YET_ANOTHER_UUID);
  childAcc2->setName("child2");

  // when
  childAcc1->setParent(parentAcc);
  childAcc2->setParent(parentAcc);

  // then
  ASSERT_EQ(*childAcc1, *(parentAcc->getChildren().at(0).lock()));
  ASSERT_EQ(*childAcc2, *(parentAcc->getChildren().at(1).lock()));
}

TEST(TestAccount, shouldCompareEqualityBasedOnlyOnUuid) {
  // given
  Account a1(A_UUID);
  a1.setName("a1");

  Account a2(A_UUID);
  a2.setName("a2");

  Account another1(ANOTHER_UUID);
  another1.setName("another1");

  Account another2(ANOTHER_UUID);
  another2.setName("another2");

  Account a1DiffUuid(ANOTHER_UUID);
  a1DiffUuid.setName("a1");

  // when

  // then
  ASSERT_TRUE(a1 == a1);
  ASSERT_TRUE(a1 == a2);
  ASSERT_FALSE(a1 == another1);
  ASSERT_FALSE(a1 == another2);
  ASSERT_TRUE(another1 == another2);
  ASSERT_FALSE(a1 == a1DiffUuid);
}

TEST(TestAccount, shouldTriggerMemberObserverEvents) {
  // given
  Account acc(A_UUID);
  MockModelObserver obs(acc);

  {
    InSequence dummy;

    EXPECT_CALL(obs, willChangeValueForKey("name"));
    EXPECT_CALL(obs, didChangeValueForKey("name"));

    EXPECT_CALL(obs, willChangeValueForKey("description"));
    EXPECT_CALL(obs, didChangeValueForKey("description"));

    EXPECT_CALL(obs, willChangeValueForKey("type"));
    EXPECT_CALL(obs, didChangeValueForKey("type"));
  }

  // when
  acc.setName("A name");
  acc.setDescription("A description");
  acc.setType(AccountType::Asset);

  // then (mock expectations implicitly verified)
}
