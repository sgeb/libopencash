#include "opencash/model/ObservableModel.h"

namespace opencash { namespace model {

  using std::string;

  void ObservableModel::willChangeValueForKey(string key)
  {
    willChangeValueForKeyEvent.notify(this, EventArgs(key));
  }

  void ObservableModel::didChangeValueForKey(string key)
  {
    didChangeValueForKeyEvent.notify(this, EventArgs(key));
  }

  void ObservableModel::willChangeIndexedValueForKey(string key, size_t index,
      ObservedChange change)
  {
    willChangeIndexedValueForKeyEvent.notify(this,
        EventArgs(key, index, change));
  }

  void ObservableModel::didChangeIndexedValueForKey(string key, size_t index,
      ObservedChange change)
  {
    didChangeIndexedValueForKeyEvent.notify(this,
        EventArgs(key, index, change));
  }

}}
