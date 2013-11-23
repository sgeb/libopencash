#include "opencash/model/AccountsMeta.h"

#include <sstream>
#include <iostream>

namespace opencash { namespace model {

  std::size_t AccountsMeta::getCount() const
  {
    return _count;
  }

  void AccountsMeta::setCount(std::size_t count)
  {
    willChange("count");
    _count = count;
    didChange("count");
  }

}}
