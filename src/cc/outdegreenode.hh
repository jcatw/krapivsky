#ifndef BIGNET_OUTDEGREENODE_H
#define BIGNET_OUTDEGREENODE_H

#include "common.hh"
#include "degreenode.hh"

namespace bignet {
  class OutDegreeNode : public DegreeNode {
  public:
    uint64_t get_value() {return out_degree;}
  };
}

#endif /* BIGNET_OUTDEGREENODE_H */
