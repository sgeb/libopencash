#ifndef __OC_CONTROLLER_MODELOBSERVER_H_
#define __OC_CONTROLLER_MODELOBSERVER_H_

#include "opencash/model/ObservableModel.h"

#include <string>

using std::string;
using opencash::model::ObservableModel;
using ObservedChange = opencash::model::ObservableModel::ObservedChange;
using EventArgs = opencash::model::ObservableModel::EventArgs;

namespace opencash { namespace controller {

  class ModelObserver {
    public:
      ModelObserver(model::ObservableModel & model);
      virtual ~ModelObserver();

    protected:
      model::ObservableModel & _model;

      virtual void willChangeValueForKey(const string & key) = 0;
      virtual void didChangeValueForKey(const string & key) = 0;

      virtual void willChangeIndexedValueForKey(const string & key,
          const size_t & index, const ObservedChange & change) = 0;

      virtual void didChangeIndexedValueForKey(const string & key,
          const size_t & index, const ObservedChange & change) = 0;

    private:
      void willChangeValueForKey(const EventArgs & args);
      void didChangeValueForKey(const EventArgs & args);
      void willChangeIndexedValueForKey(const EventArgs & args);
      void didChangeIndexedValueForKey(const EventArgs & args);
  };

}}

#endif
