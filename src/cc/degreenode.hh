#ifndef BIGNET_DEGREENODE_H
#define BIGNET_DEGREENODE_H

#include "common.hh"
#include "node.hh"

namespace bignet {
  class DegreeNode: public Node {
  public:
    DegreeNode();
    DegreeNode(uint64_t id);
    uint64_t in_degree = 0;
    uint64_t out_degree = 0;

    void add_edge (Node* to);
  };
}
#endif
