#ifndef LSH_H
#define LSH_H
#include <vector>
#include "hash_f.h"

void lsh_hash_curves(int k, int w, int v_size, int dimension, int tablesize,
  const std::vector<std::vector<norm_curve>> & Lcurves);

#endif
