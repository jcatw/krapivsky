#ifndef BIGNET_OUTDEGREEBSTREAPITEM_H
#define BIGNET_OUTDEGREEBSTREAPITEM_H

#include "common.hh"
#include "bstreapitem.hh"

namespace bignet {
  class OutDegreeBstreapItem : public BstreapItem {
  public:
    OutDegreeBstreapItem(DegreeNode* node, double fitness);
  };
}
#endif /* BIGNET_OUTDEGREEBSTREAPITEM_H */
