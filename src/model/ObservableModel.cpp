#include "opencash/model/ObservableModel.h"

namespace opencash { namespace model {

  using std::string;

  void ObservableModel::willChange(string key)
  {
    willChangeEvent.notify(this, EventArgs(key));
  }

  void ObservableModel::didChange(string key)
  {
    didChangeEvent.notify(this, EventArgs(key));
  }

  void ObservableModel::willChangeAtIndex(string key, size_t index,
      ChangeType change)
  {
    willChangeAtIndexEvent.notify(this, EventArgs(key, index, change));
  }

  void ObservableModel::didChangeAtIndex(string key, size_t index,
      ChangeType change)
  {
    didChangeAtIndexEvent.notify(this, EventArgs(key, index, change));
  }

}}
