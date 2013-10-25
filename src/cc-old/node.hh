#ifndef BIGNET_NODE_H
#define BIGNET_NODE_H

#include "common.hh"
#include "nodepair.hh"

namespace bignet {
  class Node {
  public:
    Node();
    Node(uint64_t id);
    uint64_t id;
    NodePair* adjacency_list = (NodePair*) NULL;

    virtual void add_edge (Node* to);
  };
}
#endif
