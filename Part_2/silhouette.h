#ifndef SILHOUETTE_H
#define SILHOUETTE_H

#include <string>
#include <vector>

#include "curve.h"

void compute_silhuette(std::vector<real_curve *> & centroids,
  std::vector<std::vector<real_curve *>> & assignment, std::string dist,
  std::vector<double> & Si, double & Stotal);

#endif
