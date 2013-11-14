#ifndef __OC_MODEL_ACCOUNTSMETA_H_
#define __OC_MODEL_ACCOUNTSMETA_H_

#include "opencash/model/ObservableModel.h"
#include "opencash/model/Account.h"

#include <odb/core.hxx>

namespace opencash { namespace model {

  #pragma db view object(Account)
  class AccountsMeta : public ObservableModel {
    friend class odb::access;

    public:
      std::size_t getCount() const;

    private:
      void setCount(std::size_t count);

    private:
      #pragma db column("count(*)") set(setCount)
      std::size_t _count;
  };

}}

#endif
