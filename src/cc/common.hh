#ifndef BIGNET_COMMON_H
#define BIGNET_COMMON_H

#include <cstdint>
#include <cstddef>
#include <stdlib.h>
#include <iostream>


namespace bignet {
  // forward declare everything
  template<class T> class Bstreap;
  template<class T> class BstreapItem;
  class DegreeNode;
  class InDegreeNode;
  class KrapivskyModel;
  class OutDegreeNode;
  template<class T> class Network;
  extern double uniform_random_double();
  extern double random_double();
}



#endif /* BIGNET_COMMON_H */
