#include "opencash/controller/ModelObserver.h"
#include "opencash/model/ObservableModel.h"

#include <Poco/delegate.h>

namespace opencash { namespace controller {

  ModelObserver::ModelObserver(model::ObservableModel & model)
  {
    model.willChangeValueForKeyEvent +=
      Poco::delegate(this, &ModelObserver::willChangeValueForKey);
    model.didChangeValueForKeyEvent +=
      Poco::delegate(this, &ModelObserver::didChangeValueForKey);
  }

}}
