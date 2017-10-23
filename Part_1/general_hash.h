#ifndef GENERAL_HASH_H
#define GENERAL_HASH_H

#include "curve.h"
#include "entry.h"

void hash_curves(const std::vector<std::vector<norm_curve>> & Lcurves,
  int dimension, std::vector<std::vector<std::vector<entry>>> & Lhashtable,
  int tablesize, std::vector<real_curve*> & curves,
  std::vector<real_curve> & normalized_curves, std::string hash, int k, int w);

//returns a vector of factors r
//use in classic and lsh
void init_r(int dimension,std::vector<int> & r);

//returns the hash key
//use in classic and lsh
void linear_combination(const std::vector<int> & cur_points,
  const std::vector<int> & r, int & key, int tablesize);

//prints the given hash table
//used in both classic and lsh
//mostly used for test reasons
void print_hashtable(std::vector<std::vector<entry>> & ht, int tablesize);

#endif
