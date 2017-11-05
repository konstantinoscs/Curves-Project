#ifndef CLASSIC_HASH_H
#define CLASSIC_HASH_H

#include <vector>

#include "curve.h"
#include "entry.h"

//hash the concat curve and insert
//it into the hash table
void classic_curve_hashing(
	const std::vector<int> & cnp,//concatenated points as vector with size:d*max*k
	std::vector<int> & r,//vector Ri with size:d*max*k
  std::vector<entry> *ht,//hastable
  int tablesize,//hashtable's size
  std::vector<real_curve*> & curves,//curves pointers
  int curve_index,//index in vector "curves" of the curve we hash now
  std::vector<real_curve> & normalized_curves//grid curves
);


#endif
