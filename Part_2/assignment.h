#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <vector>
#include "curve.h"

double lloyds_assignment(std::vector<real_curve *> & centroids,
  std::vector<real_curve *> & curves,
  std::vector<std::vector<real_curve *>> & assignment);

#endif
