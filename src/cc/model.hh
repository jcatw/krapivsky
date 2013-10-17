#ifndef BIGNET_MODEL_H
#define BIGNET_MODEL_H

#include "common.hh"
#include "network.hh"

namespace bignet {
  class Model {
  public:
    virtual ~Model();
    Model();
    virtual Network* next(Network* network) =0;
    virtual int done(Network *network) =0;
  };
}

#endif
