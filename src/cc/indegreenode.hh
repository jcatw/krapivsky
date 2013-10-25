#ifndef BIGNET_INDEGREENODE_H
#define BIGNET_INDEGREENODE_H

#include "common.hh"
#include "degreenode.hh"

namespace bignet {
  class InDegreeNode : public DegreeNode {
  public:
    uint64_t get_value() {return in_degree;}
  };
}

#endif /* BIGNET_INDEGREENODE_H */
