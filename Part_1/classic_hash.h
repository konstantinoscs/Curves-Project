#ifndef CLASSIC_HASH_H
#define CLASSIC_HASH_H

#include <vector>

#include "curve.h"
#include "entry.h"

//hash the cur into the array[N/4]
//maybe used in both classic and lsh
void classic_curve_hashing(const std::vector<int> & cnp,std::vector<int> & r,
  std::vector<entry> *ht,int tablesize,
  std::vector<real_curve*> & curves, int curve_index,
  std::vector<real_curve> & normalized_curves);


#endif
