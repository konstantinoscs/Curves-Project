#ifndef LSH_H
#define LSH_H

#include <vector>
#include "hash_f.h"
#include "assign_entry.h"

//makes k hash functions and puts them in hs
void make_hashes(std::vector<hash_f> & hs, int w, int v_size, int kvec);

//choose k h_i randomly, the indexes of the hash functions are
//put in an int vector g
void make_g(const std::vector<hash_f> & hs, std::vector<int> & g);

//the lsh hashing
void lsh_curve_hashing(const std::vector<int> & concat_norm_points,
  const std::vector<int> & r, std::vector<assign_entry*> *ht, int tablesize,
  int curve_index, std::vector<assign_entry> & entries, std::vector<int> & g,
  std::vector<hash_f> & hs);

#endif
