#ifndef __OC_MODEL_OBSERVABLEMODEL_H_
#define __OC_MODEL_OBSERVABLEMODEL_H_

#include <Poco/BasicEvent.h>
#include <string>

using std::string;

namespace opencash { namespace model {

  class ObservableModel {
    public:
      Poco::BasicEvent<string> willChangeValueForKeyEvent;
      Poco::BasicEvent<string> didChangeValueForKeyEvent;

    protected:
      void willChangeValueForKey(string key);
      void didChangeValueForKey(string key);
  };

} }

#endif
