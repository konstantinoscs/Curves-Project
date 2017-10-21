#ifndef LSH_H
#define LSH_H

#include <vector>
#include "hash_f.h"

void make_hashes(std::vector<hash_f> & hs, int w, int v_size, int k);

void make_g(const std::vector<hash_f> hs, int * g);

void lsh_hash_curves(int k, int w, int v_size, int dimension, int tablesize,
  const std::vector<std::vector<norm_curve>> & Lcurves);

#endif
