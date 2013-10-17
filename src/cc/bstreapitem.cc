#include "bstreapitem.hh"

namespace bignet {
  // insert an item into the bstreap
  void BstreapItem::insert(BstreapItem *item) {
    total_mass += item->get_my_mass();

    if (go_left_comparison(item)) {
        if(left == NULL) { //nothing to the left
          left = item;
        }
        else { //something to the left
          left->insert(item);
        }
        if (left->priority > priority) { //maintain heap property
            rotate_right(this);
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
          rotate_left(this);
        }
    }
  }

  BstreapItem* BstreapItem::sample(Bstreap* bstreap, double uniform_sample, double total) {
    if (left != NULL) {
        if (uniform_sample < (total + left->get_total_mass()) / bstreap->total;
                  
  }

  BstreapItem* BstreapItem::sample_destructive(double uniform_sample) {
    
  }

  static void BstreapItem::rotate_left(HeapNode *& heapnode) {
    HeapNode *P;
    HeapNode *Q;
    HeapNode *Q_left;

    double P_total;
    double fulltotal = ((BstreapItem*) heapnode)->get_total_mass();

    P = heapnode;
    Q = p->get_right();
    if (Q != NULL) {
        Q_left = Q->get_left();
      }
    else {
      Q->left = NULL;
    }
    heapnode = Q;
    ((BstreapItem*) heapnode)->set_total_mass(fulltotal);
    
    P->set_right(Q_left);

    P_total = fulltotal;
    if (Q != NULL) {
        P_total -= ((BstreapItem*) Q)->get_my_mass();
        if (Q->get_right != NULL) {
            P_total -= ((BstreapItem*) Q->get_right)->get_total_mass();
          }
      }
    ((BstreapItem)* P)->set_total_mass(P_total);
    
    heapnode->set_left(P);
  }

  static void BstreapItem::rotate_right(HeapNode *& bstreapitem) {
    HeapNode *Q;
    HeapNode *P;
    HeapNode *P_right;

    double Q_total;
    double fulltotal = ((BstreapItem*) heapnode)->get_total_mass();
    
    Q = heapnode;
    P = Q->get_left;
    if (P != NULL) {
        P_right = P->get_right;
      }
    else {
      P_right = NULL;
    }
    heapnode = P;
    ((BstreapItem*) heapnode)->set_total_mass(fulltotal);

    Q->set_left(P_right);
    Q_total = fulltotal;
    if (P != NULL) {
        Q_total -= ((BstreapItem*) P)->get_my_mass();
        if (P->get_left() != NULL) {
            Q_total -= ((BstreapItem*) P->get_left())->get_total_mass();
          }
      }
    ((BstreapItem*) P)->set_total_mass(P_mass);
    heapnode->set_right(Q);
  }
  
  HeapNode *BstreapItem::get_left() { return left; }
  HeapNode *BstreapItem::get_right() { return right; }

  void *BstreapItem::set_left(HeapNode *left) { this->left = (BstreapItem*) left; }
  void *BstreapItem::set_right(HeapNode *right) { this->right = (BstreapItem*) right; }
}
