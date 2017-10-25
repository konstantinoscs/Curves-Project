#ifndef SEARCH_OPS_H
#define SEARCH_OPS_H

#include <vector>
#include <string>

#include "curve.h"
#include "entry.h"

//gets the search curves and returns for everyone of them
//1.a pointer to the nearest curve
//2.the distance between them
//3.if the same grid curve was found in hash table
//all of them in vectors with size=s_curves.size() each of them
void search_curves(std::vector<real_curve> & s_curves,
  std::vector<std::vector<std::vector<entry>>> & Lht,
  int k, int v_size, int dimension, double delta, int tablesize,
  std::string hash,std::string dist, std::vector<real_curve*> & pcurves,
  bool stats, double R, real_curve** nn_curve,double* nn_distance,
  bool* grid_curve_found, std::vector<std::string> * curves_in_R, int w);

//finds the (1)curve and (2)distance between the scurve and
//the nearest curve in a vector of (pointers of) curves
void find_nn(real_curve & scurve,std::vector<real_curve*> pcurves,
	int dimension,std::string dist, real_curve* & nneigh,double & distance,
	bool stats, double R, std::vector<std::string> & curves_in_R_i);

#endif
