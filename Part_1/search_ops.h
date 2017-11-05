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
//4.ids from curves in less-equal distance than R(only if stats==false)
//5.the elapsed_time we need to find them
//all of them in vectors with size=s_curves.size() each of them
void search_curves(std::vector<real_curve> & s_curves,//original search curves
  std::vector<std::vector<std::vector<entry>>> & Lht,//the L hashtables
  int k, int v_size,//v_size==max
  int dimension, double delta, int tablesize,//tablesize==hashtable's size
  std::string hash, std::string dist,//specifiers for hash and distance funcions
  std::vector<real_curve*> & pcurves,//pointers to original curves
  bool stats, double R, real_curve** nn_curve,//[output]:1
  double* nn_distance,//[output]:2
  bool* grid_curve_found,//[output]:3
  std::vector<std::string> * curves_in_R,//[output]:4
  int w, double* elapsed_time//[output]:5
);

//finds the (1)curve and (2)distance between the scurve and
//the nearest curve in a vector of (pointers of) curves
//(3)all curve ids that have distance <=R with the scurve
void find_nn(real_curve & scurve,std::vector<real_curve*> pcurves,
	int dimension,std::string dist, real_curve* & nneigh,//[output]:1
	double & distance,//[output]:2
	bool stats, double R, std::vector<std::string> & curves_in_R_i//[output]:3
);

#endif
