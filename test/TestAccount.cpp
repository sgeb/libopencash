#include "opencash/model/Account.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace opencash::model;
using namespace std;
using namespace ::testing;
using AccountType = opencash::model::Account::AccountType;

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

    EXPECT_CALL(obs, willChange("name"));
    EXPECT_CALL(obs, didChange("name"));

    EXPECT_CALL(obs, willChange("description"));
    EXPECT_CALL(obs, didChange("description"));

    EXPECT_CALL(obs, willChange("type"));
    EXPECT_CALL(obs, didChange("type"));
  }

  // when
  acc.setName("A name");
  acc.setDescription("A description");
  acc.setType(AccountType::Asset);

  // then (mock expectations implicitly verified)
}

TEST(TestAccount, shouldTriggerParentChildrenObserverEvents) {
  // given
  auto parentAcc = make_shared<Account>(A_UUID);
  MockModelObserver parentObs(*parentAcc);

  auto childAcc1 = make_shared<Account>(ANOTHER_UUID);
  MockModelObserver childObs1(*childAcc1);

  auto childAcc2 = make_shared<Account>(YET_ANOTHER_UUID);
  MockModelObserver childObs2(*childAcc2);

  {
    using opencash::model::ObservableModel::ChangeType::Insertion;
    using opencash::model::ObservableModel::ChangeType::Removal;

    InSequence dummy;

    EXPECT_CALL(childObs1, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 0, Insertion));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 0, Insertion));
    EXPECT_CALL(childObs1, didChange("parent"));

    EXPECT_CALL(childObs2, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 1, Insertion));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 1, Insertion));
    EXPECT_CALL(childObs2, didChange("parent"));

    EXPECT_CALL(childObs1, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 0, Removal));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 0, Removal));
    EXPECT_CALL(childObs1, didChange("parent"));
  }

  // when
  childAcc1->setParent(parentAcc);
  childAcc2->setParent(parentAcc);
  childAcc1->setParent(NULL);

  // then (mock expectations implicitly verified)
}
