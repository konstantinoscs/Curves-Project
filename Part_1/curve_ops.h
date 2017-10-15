#ifndef CURVE_OPS_H
#define CURVE_OPS_H

#include "curve.h"

/*makes cur a grid curve by converting ur_curve's points into grid points
  also looks for min and max*/
void curve_reduction(const real_curve & ur_curve, double delta,
  real_curve & cur, int & min, int & max);

//returns a d-dimension vector with coordinates in [0,delta)
void chosen_t(double delta, int dimension, std::vector<double> & t);

/*adds t to norm_points then converts every coordinate into
  integer and adds zero_points to moved_points vector until
  he has 'max' size*/
void curve_move(const std::vector<std::vector<double>> & norm_points,
  const std::vector<double> & t, const int & max, const double & delta,
  const int & dimension,std::vector<std::vector<int>> & moved_points);

  /*  makes concat_normalized_curves an L dimension vector
      with curves.size() curves and every curve
      has k*max(curve_points) points!

      use in curve_search:
          same but this time L=1*/
void Lconcatenate_kcurves(const int & k, const int & L,
  const std::vector<real_curve> & curves, const int & dimension, const double & delta,
  std::vector< std::vector< norm_curve >> & concat_normalized_curves);

#endif
