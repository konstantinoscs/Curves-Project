#ifndef RANGE_ASSIGN_H
#define RANGE_ASSIGN_H

#include <vector>
#include "assign_entry.h"

void init_assign_entries(vector<assign_entry> & entries,
  vector<real_curve> & curves);

void init_hashtable(int L, int k, const std::vector<assign_entry> & entries,
  int dimension, double  delta, const std::vector<real_curve*> & centroids,
  int kvec, int w, const vector<real_curve> & curves, int tablesize,
  std::vector<std::vector<std::vector<assign_entry*>>> &Lht,
  int** centroid_keys);//centroid_keys = array[L][c]


#endif
