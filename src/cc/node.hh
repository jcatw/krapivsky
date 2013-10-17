#ifndef BIGNET_NODE_H
#define BIGNET_NODE_H

#include "common.hh"
#include "nodepair.hh"

namespace bignet {
  class Node {
  public:
    uint64_t id;
    NodePair* adjacency_list = (NodePair*) NULL;

    Node(uint64_t id) {this->id = id;}

    virtual void add_edge (Node* to);
  };
}
#endif
