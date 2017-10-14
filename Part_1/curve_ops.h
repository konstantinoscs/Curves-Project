#ifndef CURVE_OPS_H
#define CURVE_OPS_H

#include "curve.h"

curve curve_reduction(const curve & ur_curve, double delta);

void chosen_t(double delta, int dimension, std::vector<double> & t);

void curve_move(const std::vector<std::vector<double>> & norm_points,
  const std::vector<double> & t, const int & dimension, const int & max,
  std::vector<std::vector<double>> & moved_points);

#endif
