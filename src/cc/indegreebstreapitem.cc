#include "indegreebstreapitem.hh"

namespace bignet {
  InDegreeBstreapItem::InDegreeBstreapItem(DegreeNode* node, double fitness) {
    this->node = node;
    //mass = (double) this->node->in_degree + fitness;
    set_my_mass((double) this->node->in_degree + fitness);
  }
}
