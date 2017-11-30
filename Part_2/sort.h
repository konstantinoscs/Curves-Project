#ifndef SORT_H
#define SORT_H

#include <vector>

#include "curve.h"

void sort_clusters(std::vector<real_curve *> & centroids,
  std::vector<std::vector<real_curve *>> & assignment,int x);

#endif
