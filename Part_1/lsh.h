#ifndef LSH_H
#define LSH_H

#include <vector>
#include "hash_f.h"

//makes k hash functions and puts them in hs
void make_hashes(std::vector<hash_f> & hs, int w, int v_size, int k);

//choose k h_i randomly, the indexes of the hash functions are
//put in an int array g
void make_g(const std::vector<hash_f> & hs, int * g);

//the lsh hashing, most probably will be omitted and integrated in
//hash_curves of "classic_hash.cpp"
void lsh_hash_curves(int k, int w, int v_size, int dimension, int tablesize,
  const std::vector<std::vector<norm_curve>> & Lcurves);

#endif
