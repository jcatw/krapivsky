#include "bstreapitem.hh"

namespace bignet {
  // insert an item into the bstreap
  void BstreapItem::insert(BstreapItem *item) {
    BstreapItem *mutable_this = this;
    total_mass += item->get_my_mass();

    if (go_left_comparison(item)) {
      if(get_left() == NULL) { //nothing to the left
        left = item;
      }
      else { //something to the left
        get_left()->insert(item);
      }
      if (get_left()->priority > priority) { //maintain heap property
        rotate_right(mutable_this);
      }
    }
    else {
      if (right == NULL) { //nothing to the right
        right = item;
      }
      else { //something to the right
        right->insert(item);
      }
      if (right->priority > priority) { //maintain heap property
          rotate_left(mutable_this);
        }
    }
  }

  BstreapItem* BstreapItem::sample(Bstreap* bstreap, double uniform_sample, double total) {
    if (get_left() != NULL) {
      if (uniform_sample < (total + get_left()->get_total_mass()) / bstreap->total_mass) 
        return get_left()->sample(bstreap, uniform_sample, total);
      total += get_left()->get_total_mass();
    }
    total += get_my_mass();
    if (uniform_sample < total / bstreap->total_mass)
      return this;
    if (get_right() != NULL)
      return get_right()->sample(bstreap, uniform_sample, total);
    return NULL; //should not happen!
  }

  BstreapItem* BstreapItem::sample_destructive(Bstreap *bstreap, double uniform_sample, double total) {
    BstreapItem *returned_item;
    if (get_left() != NULL) {
      if (uniform_sample < (total + get_left()->get_total_mass()) / bstreap->total_mass) {
        returned_item = get_left()->sample_destructive(bstreap, uniform_sample, total);
        this->set_total_mass(this->get_total_mass() - returned_item->get_my_mass());
        return returned_item;
      }
      total += get_left()->get_total_mass();
    }
    total += get_my_mass();
    if (uniform_sample < total / bstreap->total_mass)
      return this;
    if (get_right() != NULL) {
      returned_item = get_right()->sample(bstreap, uniform_sample, total);
      this->set_total_mass(this->get_total_mass() - returned_item->get_my_mass());
      return returned_item;
    }
    return NULL; //should not happen!
  }

  void BstreapItem::rotate_left(BstreapItem *& bstreapitem) {
    BstreapItem *P;
    BstreapItem *Q;
    BstreapItem *Q_left;

    double P_total;
    double fulltotal = bstreapitem->get_total_mass();

    P = bstreapitem;
    Q = P->get_right();
    if (Q != NULL) {
      Q_left = Q->get_left();
    }
    else {
      Q_left = NULL;
    }
    bstreapitem = Q;
    bstreapitem->set_total_mass(fulltotal);
    
    P->set_right(Q_left);

    P_total = fulltotal;
    if (Q != NULL) {
      P_total -= ((BstreapItem*) Q)->get_my_mass();
      if (Q->get_right() != NULL) {
        P_total -= ((BstreapItem*) Q->get_right())->get_total_mass();
      }
    }
    //((BstreapItem)* P)->set_total_mass(P_total);
    P->set_total_mass(P_total);
    bstreapitem->set_left(P);
  }

  void BstreapItem::rotate_right(BstreapItem *& bstreapitem) {
    BstreapItem *Q;
    BstreapItem *P;
    BstreapItem *P_right;

    double Q_total;
    //double fulltotal = bstreapitem->get_total_mass();
    double fulltotal = bstreapitem->get_total_mass();
    
    Q = bstreapitem;
    P = Q->get_left();
    if (P != NULL) {
      P_right = P->get_right();
    }
    else {
      P_right = NULL;
    }
    bstreapitem = P;
    bstreapitem->set_total_mass(fulltotal);

    Q->set_left(P_right);
    Q_total = fulltotal;
    if (P != NULL) {
      Q_total -= ((BstreapItem*) P)->get_my_mass();
      if (P->get_left() != NULL) {
        Q_total -= ((BstreapItem*) P->get_left())->get_total_mass();
      }
    }
    //((BstreapItem*) Q)->set_total_mass(Q_total);
    Q->set_total_mass(Q_total);
    bstreapitem->set_right(Q);
  }

  void BstreapItem::remove(Bstreap *bstreap) {
    BstreapItem *mutable_this = this;
    int left = 0;
    BstreapItem *parent = NULL;
    while(get_left() != NULL || get_right() != NULL) {
      if(get_left() == NULL) {
        parent = this;
        rotate_left(mutable_this);
        left = 1;
      }
      else if (get_right() == NULL) {
        parent = this;
        rotate_right(mutable_this);
        left = 0;
      }
      else if (get_left()->priority > get_right()->priority) {
        parent = this;
        rotate_right(mutable_this);
        left = 0;
      }
      else {
        parent = this;
        rotate_left(mutable_this);
        left = 1;
      }
    }
    if (parent == NULL)
      bstreap->root = NULL;
    else if (left)
      parent->set_left(NULL);
    else
      parent->set_right(NULL);

    delete this;
  }
  
  BstreapItem *BstreapItem::get_left() { return left; }
  BstreapItem *BstreapItem::get_right() { return right; }

  void *BstreapItem::set_left(HeapNode *left) { this->left = (BstreapItem*) left; }
  void *BstreapItem::set_right(HeapNode *right) { this->right = (BstreapItem*) right; }

  int BstreapItem::go_left_comparison(BstreapItem *item) {
    if (item->get_my_mass() <= get_my_mass())
      return 1;
    return 0;
  }
}
