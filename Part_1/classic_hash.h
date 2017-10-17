#ifndef CLASSIC_HASH_H
#define CLASSIC_HASH_H

#include "curve.h"

void classic_hash_curves(const std::vector<std::vector<norm_curve>> & curves,
 int dimension, std::vector<std::vector<std::vector<std::string>>> Lhashtable,
 int tablesize);

//returns a vector of factors r
//use in classic and lsh
void init_r(int dimension,std::vector<int> & r);

//returns the hash key
//use in classic and lsh
void linear_combination(const std::vector<int> & cur_points,
  const std::vector<int> & r, int & key);

//hash the cur into the array[N/4]
//maybe used in both classic and lsh
void curve_hashing(const norm_curve & cur,std::vector<int> & r,
  std::vector<std::string> *ht,int tablesize);

#endif
