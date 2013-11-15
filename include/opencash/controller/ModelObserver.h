#ifndef __OC_CONTROLLER_MODELOBSERVER_H_
#define __OC_CONTROLLER_MODELOBSERVER_H_

#include <string>
using std::string;

namespace opencash { namespace model {
  class ObservableModel;
}}

namespace opencash { namespace controller {

  class ModelObserver {
    public:
      ModelObserver(model::ObservableModel & model);

    protected:
      virtual void willChangeValueForKey(const string & key) = 0;
      virtual void didChangeValueForKey(const string & key) = 0;
  };

}}

#endif
