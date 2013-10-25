#include "degreenode.hh"

namespace bignet {
  DegreeNode::DegreeNode() {
    this->id = 0;
  }
  DegreeNode::DegreeNode(uint64_t id) {
    this->id = id;
  }
  void DegreeNode::add_edge(Node* to) {
    Node::add_edge(to);
    out_degree++;
    ((DegreeNode*) to)->in_degree++;
  }
}


