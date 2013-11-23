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
      enum class ObservedChange {
        Setting,      // when setting to-one properties
        Insertion,    // when inserting an element into to-many properties
        Removal,      // when removing an element from to-many properties
        Replacement,  // when replacing an element in to-many properties
      };

      class EventArgs {
        public:
          EventArgs(string k, size_t i = 0,
              ObservedChange c = ObservedChange::Setting)
            : key(k), index(i), change(c) {}

          string key;
          size_t index;
          ObservedChange change;
      };

    public:
      BasicEvent<const EventArgs> willChangeValueForKeyEvent;
      BasicEvent<const EventArgs> didChangeValueForKeyEvent;

      BasicEvent<const EventArgs> willChangeIndexedValueForKeyEvent;
      BasicEvent<const EventArgs> didChangeIndexedValueForKeyEvent;

    protected:
      void willChangeValueForKey(string key);
      void didChangeValueForKey(string key);

      void willChangeIndexedValueForKey(string key, size_t index,
          ObservedChange change);

      void didChangeIndexedValueForKey(string key, size_t index,
          ObservedChange change);
  };

}}

#endif
