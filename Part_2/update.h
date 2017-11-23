#ifndef UPDATE_H
#define UPDATE_H

#include "curve.h"

//mean frechet chooses a centroid which is not part of the
//dataset
double mean_discrete_frechet(std::vector<real_curve *> & centroids,
  std::vector<std::vector<real_curve *>> & assignment, double objective);

//pam chooses a medoid
double pam_update(std::vector<real_curve *> & centroids,
  std::vector<std::vector<real_curve *>> & assignment, double objective);

#endif
