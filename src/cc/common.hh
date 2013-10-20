#ifndef BIGNET_COMMON_H
#define BIGNET_COMMON_H

#include <cstdint>
#include <cstddef>
#include <stdlib.h>

namespace bignet {

  // forward declare everything
  class Bstreap;
  class BstreapItem;
  class DegreeNode;
  class DirectedDegreeNetwork;
  class HeapNode;
  class InDegreeBstreapItem;
  class KrapivskyModel;
  class Model;
  class Network;
  class Node;
  class NodePair;
  class NodeSet;
  class OutDegreeBstreapItem;
  class Simulation;
 
}

double uniform_random();
#endif
