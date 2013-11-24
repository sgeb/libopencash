#include "opencash/controller/ModelObserver.h"
#include "opencash/model/ObservableModel.h"

#include <Poco/delegate.h>

namespace opencash { namespace controller {
  using EventArgs = opencash::model::ObservableModel::EventArgs;
  using MyDelegate = Poco::Delegate<ModelObserver, const EventArgs, false>;

  ModelObserver::ModelObserver(model::ObservableModel & model) :
    _model(model)
  {
    _model.willChangeEvent += MyDelegate(this, &ModelObserver::willChange);

    _model.didChangeEvent += MyDelegate(this, &ModelObserver::didChange);

    _model.willChangeAtIndexEvent +=
      MyDelegate(this, &ModelObserver::willChangeAtIndex);

    _model.didChangeAtIndexEvent +=
      MyDelegate(this, &ModelObserver::didChangeAtIndex);
  }

  ModelObserver::~ModelObserver()
  {
    _model.willChangeEvent -= MyDelegate(this, &ModelObserver::willChange);

    _model.didChangeEvent -= MyDelegate(this, &ModelObserver::didChange);

    _model.willChangeAtIndexEvent -=
      MyDelegate(this, &ModelObserver::willChangeAtIndex);

    _model.didChangeAtIndexEvent -=
      MyDelegate(this, &ModelObserver::didChangeAtIndex);
  }

  model::ObservableModel & ModelObserver::getModel() const {
    return _model;
  }

  void ModelObserver::willChange(const EventArgs & args)
  {
    willChange(args.key);
  }

  void ModelObserver::didChange(const EventArgs & args)
  {
    didChange(args.key);
  }

  void ModelObserver::willChangeAtIndex(const EventArgs & args)
  {
    willChangeAtIndex(args.key, args.index, args.change);
  }

  void ModelObserver::didChangeAtIndex(const EventArgs & args)
  {
    didChangeAtIndex(args.key, args.index, args.change);
  }

}}
