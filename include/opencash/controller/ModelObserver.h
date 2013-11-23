#ifndef __OC_CONTROLLER_MODELOBSERVER_H_
#define __OC_CONTROLLER_MODELOBSERVER_H_

#include "opencash/model/ObservableModel.h"

#include <string>

using std::string;
using opencash::model::ObservableModel;
using ChangeType = opencash::model::ObservableModel::ChangeType;
using EventArgs = opencash::model::ObservableModel::EventArgs;

namespace opencash { namespace controller {

  class ModelObserver {
    public:
      ModelObserver(model::ObservableModel & model);
      virtual ~ModelObserver();

    protected:
      model::ObservableModel & _model;

      virtual void willChange(const string & key) = 0;
      virtual void didChange(const string & key) = 0;

      virtual void willChangeAtIndex(const string & key,
          const size_t & index, const ChangeType & change) = 0;

      virtual void didChangeAtIndex(const string & key,
          const size_t & index, const ChangeType & change) = 0;

    private:
      void willChange(const EventArgs & args);
      void didChange(const EventArgs & args);
      void willChangeAtIndex(const EventArgs & args);
      void didChangeAtIndex(const EventArgs & args);
  };

}}

#endif
