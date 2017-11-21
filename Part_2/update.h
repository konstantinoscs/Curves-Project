#ifndef UPDATE_H
#define UPDATE_H

#include "curve.h"

void mean_frechet_dist();
int pam_update(std::vector<real_curve *> & centroids,
  std::vector<std::vector<real_curve *>> & assignment, int objective);

#endif
