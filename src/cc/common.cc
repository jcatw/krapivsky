#include "common.hh"

namespace bignet {
  double uniform_random_double() {return ((double) rand()) / ((double) RAND_MAX);}
  double random_double() {return (double) rand();}
}

