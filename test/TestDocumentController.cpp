#include "opencash/controller/DocumentController.h"
#include "opencash/model/Account.h"
#include "opencash/model/AccountsMeta.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using DocumentController = opencash::controller::DocumentController;
using Account = opencash::model::Account;
using AccountType = opencash::model::Account::AccountType;
using AccountPtr = opencash::model::Account::AccountPtr;
using Accounts = opencash::model::Account::Accounts;
using AccountsMeta = opencash::model::AccountsMeta;

using InSequence = ::testing::InSequence;

const std::string DBFILENAME = ":memory:";
/* const std::string DBFILENAME = "Test.db"; */

class TestDocumentController : public ::testing::Test {
  protected:
    std::unique_ptr<DocumentController> _doc;

    TestDocumentController()
      : _doc(new DocumentController(DBFILENAME, true))
    {}

    AccountPtr createAnAssetAccount()
    {
      AccountPtr ret = _doc->newAccount();
      ret->setName("test account");
      ret->setDescr("This is my first asset account");
      ret->setType(AccountType::Asset);
      return ret;
    }
};

TEST_F(TestDocumentController, shouldInitializeWithRootAccount) {
  ASSERT_EQ(1, _doc->getAccountsMeta()->getCount());
  ASSERT_EQ(AccountType::Root, _doc->retrieveAccounts()->at(0)->getType());
}

TEST_F(TestDocumentController, shouldPersistOneAccount) {
  // given
  AccountPtr acc = createAnAssetAccount();

  // when
  _doc->persistAccount(*acc);

  // then
  ASSERT_EQ(2, _doc->getAccountsMeta()->getCount());
}

TEST_F(TestDocumentController, shouldPersistTwoAccounts) {
  // given
  AccountPtr acc = createAnAssetAccount();
  AccountPtr acc2 = createAnAssetAccount();

  // when
  _doc->persistAccount(*acc);
  _doc->persistAccount(*acc2);

  // then
  ASSERT_EQ(3, _doc->getAccountsMeta()->getCount());
}

TEST_F(TestDocumentController, shouldRetrieveAccounts) {
  // given
  AccountPtr acc = createAnAssetAccount();
  AccountPtr acc2 = createAnAssetAccount();
  _doc->persistAccount(*acc);
  _doc->persistAccount(*acc2);

  // when
  std::unique_ptr<Accounts> accounts = _doc->retrieveAccounts();

  // then
  ASSERT_EQ(3, accounts->size());
  ASSERT_EQ(*acc, *(accounts->at(1)));
  ASSERT_EQ(*acc2, *(accounts->at(2)));
}

TEST_F(TestDocumentController, shouldUpdateAccountsMetaAndFireEvents) {
  // given
  AccountsMeta *accMeta = _doc->getAccountsMeta();
  MockModelObserver obs(*accMeta);
  {
    InSequence dummy;
    EXPECT_CALL(obs, willChange("count"));
    EXPECT_CALL(obs, didChange("count"));
  }
  AccountPtr acc = createAnAssetAccount();

  // when
  _doc->persistAccount(*acc);

  // then (mock expectations implicitly verified)
}
