#ifndef BIGNET_INDEGREEBSTREAPITEM_H
#define BIGNET_INDEGREEBSTREAPITEM_H

#include "common.hh"
#include "degreenode.hh"
#include "bstreapitem.hh"

namespace bignet {
  class InDegreeBstreapItem: public BstreapItem {
  public:
    InDegreeBstreapItem(DegreeNode* node, double fitness);
    DegreeNode* node;
  };
}

#endif
