#ifndef LSH_H
#define LSH_H

#include <vector>
#include "hash_f.h"

//makes k hash functions and puts them in hs
void make_hashes(std::vector<hash_f> & hs, int w, int v_size, int kvec);

//choose k h_i randomly, the indexes of the hash functions are
//put in an int vector g
void make_g(const std::vector<hash_f> & hs, std::vector<int> & g);

//the lsh hashing, most probably will be omitted and integrated in
//hash_curves of "classic_hash.cpp"
void lsh_curve_hashing(const std::vector<int> & concat_norm_points,
  const std::vector<int> & r, std::vector<entry> *ht, int tablesize,
  std::vector<real_curve*> & curves, int curve_index,
  std::vector<real_curve> & normalized_curves, std::vector<int> & g,
  std::vector<hash_f> & hs);

#endif
