#ifndef BIGNET_SETITEM_H
#define BIGNET_SETITEM_H

#include "common.hh"
#include "node.hh"

namespace bignet {
  class SetItem {
  public:
    Node *node;
    SetItem() { this->node = NULL; }
    SetItem(Node *node) { this->node = node; }
    double get_my_mass() { return mass; }
    void set_my_mass(double mass) {this->mass=mass;}
  private:
    double mass = 0.;
  };
}
#endif
