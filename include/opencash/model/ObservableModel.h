#ifndef __OC_MODEL_OBSERVABLEMODEL_H_
#define __OC_MODEL_OBSERVABLEMODEL_H_

#include <Poco/BasicEvent.h>
#include <string>

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
          EventArgs(std::string k, std::size_t i = 0,
              ChangeType c = ChangeType::Setting)
            : key(k), index(i), change(c) {}

          std::string key;
          std::size_t index;
          ChangeType change;
      };

      using Event = Poco::BasicEvent<const EventArgs>;

    public:
      Event willChangeEvent;
      Event didChangeEvent;
      Event willChangeAtIndexEvent;
      Event didChangeAtIndexEvent;

    protected:
      void willChange(std::string key);
      void didChange(std::string key);

      void willChangeAtIndex(std::string key, std::size_t index,
          ChangeType change);
      void didChangeAtIndex(std::string key, std::size_t index,
          ChangeType change);
  };

}}

#endif
