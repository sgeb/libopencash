#include "opencash/controller/DocumentController.h"
#include "opencash/model/Account.h"
#include "opencash/model/AccountsMeta.h"
#include "support/TestModelObserver.h"

#include <gtest/gtest.h>

using namespace opencash::controller;
using namespace opencash::model;
using namespace std;

const string DBFILENAME = ":memory:";
/* const string DBFILENAME = "Test.db"; */

class TestDocumentController : public ::testing::Test {
  protected:
    unique_ptr<DocumentController> _doc;

    TestDocumentController()
      : _doc(new DocumentController(DBFILENAME, true))
    {
    }

    unique_ptr<Account> createAnAssetAccount()
    {
      unique_ptr<Account> ret(_doc->newAccount());
      ret->setName("test account");
      ret->setDescription("This is my first asset account");
      ret->setType(AccountType::Asset);
      return ret;
    }
};

TEST_F(TestDocumentController, shouldInitializeWithRootAccount) {
  // given

  // when

  // then
  ASSERT_EQ(1, _doc->getAccountsMeta()->getCount());
  ASSERT_EQ(AccountType::Root, _doc->retrieveAccounts()->at(0)->getType());
}

TEST_F(TestDocumentController, shouldPersistOneAccount) {
  // given
  unique_ptr<Account> acc(createAnAssetAccount());

  // when
  _doc->persistAccount(*acc);

  // then
  ASSERT_EQ(2, _doc->getAccountsMeta()->getCount());
}

TEST_F(TestDocumentController, shouldPersistTwoAccounts) {
  // given
  unique_ptr<Account> acc(createAnAssetAccount());
  unique_ptr<Account> acc2(createAnAssetAccount());

  // when
  _doc->persistAccount(*acc);
  _doc->persistAccount(*acc2);

  // then
  ASSERT_EQ(3, _doc->getAccountsMeta()->getCount());
}

TEST_F(TestDocumentController, shouldRetrieveAccounts) {
  // given
  unique_ptr<Account> acc(createAnAssetAccount());
  unique_ptr<Account> acc2(createAnAssetAccount());
  _doc->persistAccount(*acc);
  _doc->persistAccount(*acc2);

  // when
  unique_ptr<vector<unique_ptr<Account>>> accounts = _doc->retrieveAccounts();

  // then
  ASSERT_EQ(3, accounts->size());
  ASSERT_EQ(*acc, *(accounts->at(1)));
  ASSERT_EQ(*acc2, *(accounts->at(2)));
}

TEST_F(TestDocumentController, shouldUpdateAccountsMetaAndFireEvents) {
  // given
  AccountsMeta *accMeta = _doc->getAccountsMeta();
  TestModelObserver obs(*accMeta);
  unique_ptr<Account> acc(createAnAssetAccount());

  // when
  _doc->persistAccount(*acc);

  // then
  ASSERT_TRUE(obs.hasWillChangeValueBeenFiredForKey("count"));
  ASSERT_TRUE(obs.hasDidChangeValueBeenFiredForKey("count"));
}
