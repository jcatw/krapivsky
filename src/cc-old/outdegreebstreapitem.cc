#include "outdegreebstreapitem.hh"

namespace bignet {
  OutDegreeBstreapItem::OutDegreeBstreapItem(DegreeNode* node, double fitness) {
    this->node = node;
    mass = double(this->node->out_degree) + fitness;
  }
}
