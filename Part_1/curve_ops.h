#ifndef CURVE_OPS_H
#define CURVE_OPS_H

#include "curve.h"

/*make the grid representation of curve by converting ur_curve's
   points into grid points, also looks for min and max*/
void curve_reduction(const real_curve & ur_curve,//original curve
	double delta,
  real_curve & cur,//grid curve [output]
  int & min,//min of curves points [output]
  int & max);//and their max [output]

//returns a d-dimension vector with coordinates in [0,delta) uniformly
void chosen_t(double delta,
	int dimension,
	std::vector<double> & t);//[output]

/*adds t to norm_points then converts every coordinate into
  integer and adds zero_points to moved_points vector until
  he has 'max' size*/
void curve_move(
	const std::vector<std::vector<double>> & norm_points,//grid curve
  const std::vector<double> & t, int max, double delta,
  int dimension,int k,
  std::vector<std::vector<int>> & moved_points//int represent of curve [output]
);

/*makes concat_normalized_curves an L dimension vector
  with curves.size() curves and every curve
  has k*max(curve_points) points!

  use in curve_search:
    same but this time L=1*/
void Lconcatenate_kcurves(int k, int L,
  const std::vector<real_curve> & curves,//original curves
  int dimension, double delta,
  std::vector< std::vector< norm_curve >> & concat_normalized_curves,//[output]
  int & max,//[output]
  std::vector<real_curve> & normalized_curves//the grid curves [output]
);

#endif
