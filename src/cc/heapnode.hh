#ifndef BIGNET_HEAPNODE_H
#define BIGNET_HEAPNODE_H

#include "common.hh"

namespace bignet {

// HeapNode specifies the interface for nodes in the heap.
// Provides a default rotation implementation, but not much else.
class HeapNode {
public:
  uint64_t priority;

  static void rotate_left(HeapNode *& heapnode);
  static void rotate_right(HeapNode *& heapnode);
  
  virtual HeapNode *get_left() =0;
  virtual HeapNode *get_right() =0;

  virtual void *set_left(HeapNode *heapnode) =0;
  virtual void *set_right(HeapNode *heapnode) =0;
  
};

}
#endif
