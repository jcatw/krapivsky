#ifndef BIGNET_BSTREAP_H
#define BIGNET_BSTREAP_H

#include "common.hh"
#include "nodeset.hh"
#include "setitem.hh"

namespace bignet {
  class Bstreap : public NodeSet {
  public:
    int n_items;
    double total_mass = 0;
    BstreapItem *root = NULL;

    //Bstreap(BstreapItem* root) { this->root = root; }
    Bstreap();
    void insert(BstreapItem *item);
    void sample();
    void sample_destructive();
  };
}


#endif
