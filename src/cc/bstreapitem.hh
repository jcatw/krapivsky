#ifndef BIGNET_BSTREAPITEM_H
#define BIGNET_BSTREAPITEM_H

#include "common.hh"
#include "bstreap.hh"
#include "setitem.hh"
#include "heapnode.hh"

namespace bignet {
  class BstreapItem : public SetItem, HeapNode {
  public:
    BstreapItem() {this->node = NULL;}
    BstreapItem(Node* node) {this->node = node;}
    //virtual void add_mass() =0;

    //get the unnormalized probability mass of this item
    //virtual double get_my_mass() =0;

    //get the unnormalized probability mass of the subtree
    //that has this item as root
    double get_total_mass() {return total_mass;}

    // insert a BstreapItem into the Bstreap
    void insert(BstreapItem *item);

    // sample an item from the Bstreap, removing it if destructive.
    BstreapItem* sample(Bstreap* bstreap, double uniform_sample, double total);
    BstreapItem* sample_destructive(Bstreap* bstreap, double uniform_sample, double total);

    // remove an item from the Bstreap;
    void remove(Bstreap *bstreap);

    // implementation of HeapNode functions
    static void rotate_left(BstreapItem *& bstreapitem);
    static void rotate_right(BstreapItem *& bstreapitem);
    
    BstreapItem *get_left();
    BstreapItem *get_right();
    void *set_left(HeapNode* left);
    void *set_right(HeapNode* right);
    
  private:
    double total_mass = 0.0;
    BstreapItem *left = NULL;
    BstreapItem *right = NULL;

    // Set the total mass of the node.  Used by rotations.  Using this
    // elsewhere will almost certainly break the data structure, so avoid.
    void set_total_mass(double total_mass) { this->total_mass = total_mass; }

    // determines which direction to go when traversing the Bstreap
    virtual int go_left_comparison(BstreapItem *item);
  };
  //void rotate_left(BstreapItem *& bstreapitem); 
  //void rotate_right(BstreapItem *& bstreapitem);
}
#endif
