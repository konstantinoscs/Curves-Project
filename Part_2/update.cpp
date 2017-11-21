#include <vector>
#include <utility>
#include <string>
#include "curve.h"
#include "distance_ops.h"

using namespace std;

double compute_objective(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment, string func){

  double objective{}, dist{};
  //distance is a pointer to the distance function we'll use
  void (*distance)(const vector<vector<double>> & pointsA,
    const vector<vector<double>> & pointsB, double & distance);

  //initialize pointer
  if(!func.compare("DFT"))
    distance = &computeDFD;
  else
    distance = &computeDTW;

  for(size_t i=0; i<centroids.size(); i++){
    //get centroid points
    const vector<vector<double>> & c_points = centroids[i]->get_points();
    //for every curve in cluster add distance to centroid
    for(size_t j=0; j<assignment[i].size(); j++)
    (*distance)(c_points, assignment[i][j]->get_points(), dist);
    objective += dist;
  }
  return objective;
}

double pam_update(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment, double objective, string func){

  double obj{}, minobj{objective};
  vector<real_curve *> opt_config = centroids;
  real_curve * temp{nullptr};

  //start swapping every centroid
  for(size_t i=0; i<centroids.size(); i++){
    //swap with every curve in the current cluster
      for(size_t j=0; j<assignment[i].size(); j++){
        //swap centroid
        temp = centroids[i];
        centroids[i] = assignment[i][j];
        assignment[i][j] = temp;
        //compute objective
        obj = compute_objective(centroids, assignment,func);
        if(obj < minobj){
          minobj = obj;
          opt_config = centroids;
        }

      }
    }
  //now centroids has the new configuration
  centroids = std::move(opt_config);
  return minobj;
}
