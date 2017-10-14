#ifndef CURVE_OPS_H
#define CURVE_OPS_H

#include "curve.h"

real_curve curve_reduction(const real_curve & ur_curve, double delta);

void chosen_t(double delta, int dimension, std::vector<double> & t);

void curve_move(const std::vector<std::vector<double>> & norm_points,
  const std::vector<double> & t, const int & max, const double & delta,
  const int & dimension,std::vector<std::vector<int>> & moved_points);

#endif
