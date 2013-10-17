#include "indegreebstreapitem.hh"

namespace bignet {
  InDegreeBstreapItem(DegreeNode* node, double fitness) {
    this->node = node;
    mass = double(this->node->in_degree) + fitness;
  }
}
