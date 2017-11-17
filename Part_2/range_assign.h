#ifndef RANGE_ASSIGN_H
#define RANGE_ASSIGN_H

#include <vector>
#include <string>

#include "assign_entry.h"

int isCentroid(std::string id, const std::vector<real_curve*> & centroids);

void init_assign_entries(std::vector<assign_entry> & entries,
  std::vector<real_curve> & curves);

void init_hashtable(int L, int k, std::vector<assign_entry> & entries,
  int dimension, double  delta, const std::vector<real_curve*> & centroids,
  int kvec, int w, const std::vector<real_curve> & curves, int tablesize,
  std::vector<std::vector<std::vector<assign_entry*>>> &Lht,
  int** centroid_keys);//centroid_keys = array[L][c]


#endif
