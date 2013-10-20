#include "heapnode.hh"

namespace bignet {
  void HeapNode::rotate_left(HeapNode *& heapnode) {
    HeapNode *P;
    HeapNode *Q;
    HeapNode *Q_left;

    P = heapnode;
    Q = P->get_right();
    if (Q != NULL) {
      Q_left = Q->get_left();
    }
    else {
      Q_left = NULL;
    }
    heapnode = Q;
    P->set_right(Q_left);
    heapnode->set_left(P);
  }

  void HeapNode::rotate_right(HeapNode *& heapnode) {
    HeapNode *Q;
    HeapNode *P;
    HeapNode *P_right;
    Q = heapnode;
    P = Q->get_left();
    if (P != NULL) {
      P_right = P->get_right();
    }
    else {
      P_right = NULL;
    }
    heapnode = P;
    Q->set_left(P_right);
    heapnode->set_right(Q);
  }
}
