#ifndef CLASSIC_HASH_H
#define CLASSIC_HASH_H

#include "curve.h"

void classic_hash_curves(const std::vector<std::vector<norm_curve>> & Lcurves,
 int dimension,
 std::vector<std::vector<std::vector<std::vector<real_curve*>>>> & Lhashtable,
 int tablesize, std::vector<real_curve> & curves,
 std::vector<real_curve> & normalized_curves);

//returns a vector of factors r
//use in classic and lsh
void init_r(int dimension,std::vector<int> & r);

//returns the hash key
//use in classic and lsh
void linear_combination(const std::vector<int> & cur_points,
  const std::vector<int> & r, int & key,int tablesize);

//hash the cur into the array[N/4]
//maybe used in both classic and lsh
void curve_hashing(const std::vector<int> & cnp,std::vector<int> & r,
  std::vector<std::vector<real_curve*>> *ht,int tablesize,
  std::vector<real_curve> & curves, int curve_index,
  std::vector<real_curve> & normalized_curves);

//prints the given hash table
//used in both classic and lsh
//mostly used for test reasons
void print_hashtable(std::vector<std::vector<std::vector<real_curve*>>> & ht,
  int tablesize);

#endif
