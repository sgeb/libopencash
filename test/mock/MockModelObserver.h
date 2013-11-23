#ifndef __OC_MOCK_MODELOBSERVER_H_
#define __OC_MOCK_MODELOBSERVER_H_

#include "opencash/controller/ModelObserver.h"

#include <string>
#include <gmock/gmock.h>

namespace opencash { namespace model {
  class ObservableModel;
}}

using opencash::controller::ModelObserver;
using opencash::model::ObservableModel;
using ObservedChange = opencash::model::ObservableModel::ObservedChange;

class MockModelObserver : public ModelObserver {
 public:
   MockModelObserver(ObservableModel & model)
     : ModelObserver(model) {}

  MOCK_METHOD1(willChangeValueForKey, void(const std::string & key));
  MOCK_METHOD1(didChangeValueForKey, void(const std::string & key));

  MOCK_METHOD3(willChangeIndexedValueForKey,
      void(const std::string & key, const std::size_t & index, const ObservedChange & change));

  MOCK_METHOD3(didChangeIndexedValueForKey,
      void(const std::string & key, const std::size_t & index, const ObservedChange & change));
};

#endif
