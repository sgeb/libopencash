#include "opencash/model/ObservableModel.h"

namespace opencash { namespace model {

  void ObservableModel::willChangeValueForKey(std::string key)
  {
    willChangeValueForKeyEvent.notify(this, key);
  }

  void ObservableModel::didChangeValueForKey(std::string key)
  {
    didChangeValueForKeyEvent.notify(this, key);
  }

} }
