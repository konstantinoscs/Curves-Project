#ifndef RANGE_ASSIGN_H
#define RANGE_ASSIGN_H

#include <vector>
#include <string>

#include "assign_entry.h"

int isCentroid(std::string id, const std::vector<real_curve*> & centroids);

//for every curve we'll have an assign_entry
//which we'll use their fields in range search
void init_assign_entries(std::vector<assign_entry> & entries,
  std::vector<real_curve> & curves);

//creates the hashtable (without inserting the centroids)
//we keep the bucket keys were (should) belong every
//centroid in array centroid_keys
void init_hashtable(int L, int k, std::vector<assign_entry> & entries,
  int dimension, double  delta, int kvec, int w,
  const std::vector<real_curve> & curves, int tablesize,
  std::vector<std::vector<std::vector<assign_entry*>>> &Lht);

void find_keys(std::vector<std::vector<std::vector<assign_entry*>>> &Lht,
  const std::vector<real_curve*> & centroids,
  std::vector<std::vector<int>> & centroid_keys);

//until here were functions helping to init the lsh hashtable

//returns the min distance between centroids
double find_R0(const std::vector<real_curve*> & centroids,std::string dist);

#endif
