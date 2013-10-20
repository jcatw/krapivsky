#ifndef BIGNET_MODEL_H
#define BIGNET_MODEL_H

#include "common.hh"
#include "network.hh"

namespace bignet {
  class Model {
  public:
    virtual ~Model();
    Model();
    virtual void next() =0;
    virtual int done() =0;
    Network* get_network() {return network; }
    Network* network;
  };
}

#endif
