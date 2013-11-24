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

    public:
      Poco::BasicEvent<const EventArgs> willChangeEvent;
      Poco::BasicEvent<const EventArgs> didChangeEvent;
      Poco::BasicEvent<const EventArgs> willChangeAtIndexEvent;
      Poco::BasicEvent<const EventArgs> didChangeAtIndexEvent;

    protected:
      void willChange(std::string key);
      void didChange(std::string key);
      void willChangeAtIndex(std::string key, std::size_t index, ChangeType change);
      void didChangeAtIndex(std::string key, std::size_t index, ChangeType change);
  };

}}

#endif
