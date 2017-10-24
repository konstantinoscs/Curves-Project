#ifndef GENERAL_HASH_H
#define GENERAL_HASH_H

#include "curve.h"
#include "entry.h"

//main function for the hashing
//returns the L hash tables
void hash_curves(const std::vector<std::vector<norm_curve>> & Lcurves,
  int dimension, std::vector<std::vector<std::vector<entry>>> & Lhashtable,
  int tablesize, std::vector<real_curve*> & curves,
  std::vector<real_curve> & normalized_curves, std::string hash, int kvec, int w);

//returns a vector of factors r
void init_r(int dimension,std::vector<int> & r);

//returns the hash key
void linear_combination(const std::vector<int> & cur_points,
  const std::vector<int> & r, int & key, int tablesize);

//prints the given hash table
//mostly used for test reasons
void print_hashtable(std::vector<std::vector<entry>> & ht, int tablesize);

#endif
