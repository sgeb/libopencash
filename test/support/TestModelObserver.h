#ifndef __OC_TESTMODELOBSERVER_H_
#define __OC_TESTMODELOBSERVER_H_

#include "opencash/controller/ModelObserver.h"

#include <set>
#include <string>

namespace opencash { namespace model {
  class ObservableModel;
}}

class TestModelObserver : public opencash::controller::ModelObserver {
  public:
    TestModelObserver(opencash::model::ObservableModel & model)
      : ModelObserver(model) {}
    bool hasWillChangeValueBeenFiredForKey(const std::string & key) const;
    bool hasDidChangeValueBeenFiredForKey(const std::string & key) const;

  protected: // overrides of ModelObserver
    void willChangeValueForKey(const std::string & key) override;
    void didChangeValueForKey(const std::string & key) override;

  private:
    std::multiset<const std::string> _keysOfWillChangeValue;
    std::multiset<const std::string> _keysOfDidChangeValue;
};

#endif
