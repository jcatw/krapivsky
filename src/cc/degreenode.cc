
#include "degreenode.hh"

namespace bignet {
  DegreeNode::DegreeNode(uint64_t id) : id(id), in_degree(0), out_degree(0), adjacency_list() {};
  
  void DegreeNode::add_edge(DegreeNode *to) {
    this->out_degree++;
    to->in_degree++;
    adjacency_list.push_front(to);
  }
}
