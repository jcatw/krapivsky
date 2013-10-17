#ifndef BIGNET_BSTREAPITEM_H
#define BIGNET_BSTREAPITEM_H

#include "common.hh"
#include "setitem.hh"
#icnlude "heapnode.hh"

namespace bignet {
  class BstreapItem : public SetItem, HeapNode {
  public:
    //virtual void add_mass() =0;

    //get the unnormalized probability mass of this item
    //virtual double get_my_mass() =0;

    //get the unnormalized probability mass of the subtree
    //that has this item as root
    double get_total_mass() {return total_mass;}

    void insert(BstreapItem *item);

    // implementation of HeapNode functions
    static void rotate_left(HeapNode *& bstreapitem);
    static void rotate_right(HeapNode *& bstreapitem);
    HeapNode *get_left();
    HeapNode *get_right();
    void *set_left(HeapNode* left);
    void *set_right(HeapNode* right);
    
  private:
    double total_mass = 0.0;
    BstreapItem *left = NULL;
    BstreapItem *right = NULL;

    // Set the total mass of the node.  Used by rotations.  Using this
    // elsewhere will almost certainly break the data structure, so avoid.
    void set_total_mass(double total_mass) { this->total_mass = total_mass };
  };
}
#endif
