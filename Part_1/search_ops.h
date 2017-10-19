#include <vector>
#include <string>
#include "curve.h"

//gets the search curves and returns for everyone of them
//1.a pointer to the nearest curve
//2.the distance between them
//3.if the same grid curve was found in hash table
//all of them in vectors with size=s_curves.size() each of them
void search_curves(std::vector<real_curve> & s_curves,
  std::vector<std::vector<std::vector<std::vector<real_curve*>>>> & Lht,
  int k, int v_size, int dimension, int delta, int tablesize,
  std::string hash,std::string dist, std::vector<real_curve*> & pcurves,
  real_curve** nn_curve,double* nn_distance,bool* grid_curve_found);

//finds the (1)curve and (2)distance between the scurve and
//the nearest curve in a vector of (pointers of) curves
void find_nn(real_curve & scurve,std::vector<real_curve*> pcurves,
	int dimension,std::string dist, real_curve* & nneigh,double & distance);
