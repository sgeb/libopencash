#include "opencash/controller/ModelObserver.h"
#include "opencash/model/ObservableModel.h"

#include <Poco/delegate.h>

namespace opencash { namespace controller {
  typedef ::Poco::Delegate<ModelObserver, const EventArgs, false> MyDelegate;

  ModelObserver::ModelObserver(model::ObservableModel & model) :
    _model(model)
  {
    _model.willChangeValueForKeyEvent +=
      MyDelegate(this, &ModelObserver::willChangeValueForKey);

    _model.didChangeValueForKeyEvent +=
      MyDelegate(this, &ModelObserver::didChangeValueForKey);

    _model.willChangeIndexedValueForKeyEvent +=
      MyDelegate(this, &ModelObserver::willChangeIndexedValueForKey);

    _model.didChangeIndexedValueForKeyEvent +=
      MyDelegate(this, &ModelObserver::didChangeIndexedValueForKey);
  }

  ModelObserver::~ModelObserver()
  {
    _model.willChangeValueForKeyEvent -=
      MyDelegate(this, &ModelObserver::willChangeValueForKey);

    _model.didChangeValueForKeyEvent -=
      MyDelegate(this, &ModelObserver::didChangeValueForKey);

    _model.willChangeIndexedValueForKeyEvent -=
      MyDelegate(this, &ModelObserver::willChangeIndexedValueForKey);

    _model.didChangeIndexedValueForKeyEvent -=
      MyDelegate(this, &ModelObserver::didChangeIndexedValueForKey);
  }

  void ModelObserver::willChangeValueForKey(const EventArgs & args)
  {
    willChangeValueForKey(args.key);
  }

  void ModelObserver::didChangeValueForKey(const EventArgs & args)
  {
    didChangeValueForKey(args.key);
  }

  void ModelObserver::willChangeIndexedValueForKey(const EventArgs & args)
  {
    willChangeIndexedValueForKey(args.key, args.index, args.change);
  }

  void ModelObserver::didChangeIndexedValueForKey(const EventArgs & args)
  {
    didChangeIndexedValueForKey(args.key, args.index, args.change);
  }

}}
