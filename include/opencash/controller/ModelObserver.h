#ifndef __OC_CONTROLLER_MODELOBSERVER_H_
#define __OC_CONTROLLER_MODELOBSERVER_H_

#include "opencash/model/ObservableModel.h"

#include <string>

namespace opencash { namespace controller {

  class ModelObserver {
    using ChangeType = opencash::model::ObservableModel::ChangeType;
    using EventArgs = opencash::model::ObservableModel::EventArgs;

    public:
      ModelObserver(model::ObservableModel & model);
      virtual ~ModelObserver();

    protected:
      model::ObservableModel & getModel() const;

      virtual void willChange(const std::string & key) = 0;
      virtual void didChange(const std::string & key) = 0;

      virtual void willChangeAtIndex(const std::string & key,
          const size_t & index, const ChangeType & change) = 0;

      virtual void didChangeAtIndex(const std::string & key,
          const size_t & index, const ChangeType & change) = 0;

    private:
      model::ObservableModel & _model;

      void willChange(const EventArgs & args);
      void didChange(const EventArgs & args);
      void willChangeAtIndex(const EventArgs & args);
      void didChangeAtIndex(const EventArgs & args);
  };

}}

#endif
