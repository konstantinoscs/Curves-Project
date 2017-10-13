#ifndef CURVE_OPS_H
#define CURVE_OPS_H

#include "curve.h"

curve curve_reduction(const curve & ur_curve, float delta);

void chosen_t(double delta, int dimension, std::vector<double> & t);

void curve_move(std::vector<std::vector<double>> norm_points, std::vector<double> t, std::vector<std::vector<double>> & moved_points);

#endif
