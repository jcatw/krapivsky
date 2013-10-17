#include "common.hh"

namespace bignet {
  double uniform_random {
    return ((double) rand()) / ((double) RAND_MAX));
  }
}
