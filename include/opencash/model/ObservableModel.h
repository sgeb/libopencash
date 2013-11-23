#ifndef __OC_MODEL_OBSERVABLEMODEL_H_
#define __OC_MODEL_OBSERVABLEMODEL_H_

#include <Poco/BasicEvent.h>
#include <string>

using Poco::BasicEvent;
using std::string;
using std::size_t;

namespace opencash { namespace model {

  class ObservableModel {
    public:
      enum class ChangeType {
        Setting,      // when setting to-one properties
        Insertion,    // when inserting an element into to-many properties
        Removal,      // when removing an element from to-many properties
        Replacement,  // when replacing an element in to-many properties
      };

      class EventArgs {
        public:
          EventArgs(string k, size_t i = 0,
              ChangeType c = ChangeType::Setting)
            : key(k), index(i), change(c) {}

          string key;
          size_t index;
          ChangeType change;
      };

    public:
      BasicEvent<const EventArgs> willChangeEvent;
      BasicEvent<const EventArgs> didChangeEvent;
      BasicEvent<const EventArgs> willChangeAtIndexEvent;
      BasicEvent<const EventArgs> didChangeAtIndexEvent;

    protected:
      void willChange(string key);
      void didChange(string key);
      void willChangeAtIndex(string key, size_t index, ChangeType change);
      void didChangeAtIndex(string key, size_t index, ChangeType change);
  };

}}

#endif
