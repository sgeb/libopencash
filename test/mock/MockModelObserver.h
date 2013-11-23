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
using ChangeType = opencash::model::ObservableModel::ChangeType;

class MockModelObserver : public ModelObserver {
  public:
    MockModelObserver(ObservableModel & model) : ModelObserver(model) {}

    MOCK_METHOD1(willChange, void(const std::string & key));
    MOCK_METHOD1(didChange, void(const std::string & key));

    MOCK_METHOD3(willChangeAtIndex,
        void(const std::string & key,
          const std::size_t & index,
          const ChangeType & change));

    MOCK_METHOD3(didChangeAtIndex,
        void(const std::string & key,
          const std::size_t & index,
          const ChangeType & change));
};

#endif
