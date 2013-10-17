#ifndef BIGNET_PREFERENTIALNODE_H
#define BIGNET_PREFERENTIALNODE_H

#include "common.hh"

namespace bignet {
  class PreferentialNode : public Node {
  public:
    double in_degree;
    double out_degree;
  };
}
#endif
