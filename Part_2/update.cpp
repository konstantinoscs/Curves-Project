#include <vector>
#include <utility>
#include "curve.h"

using namespace std;

int pam_update(vector<real_curve *> & centroids, vector<real_curve *> & curves,
  vector<vector<real_curve *>> & assignment, int objective){

  int obj{}, minobj{objective};
  vector<real_curve *> opt_config = centroids;
  real_curve * temp{nullptr};

  //start swapping every centroid
  for(size_t i=0; i<centroids.size(); i++){
    //swap with every curve in all the clusters
    for(size_t j=0; i<centroids.size(); i++){
      for(size_t k=0; j<assignment[j].size(); j++){
        //swap centroid
        temp = centroids[i];
        centroids[i] = assignment[j][k];
        assignment[j][k] = temp;
        //compute objective

        if(obj < minobj){
          minobj = obj;
          opt_config = centroids;
        }

      }
    }
  }
  //now centroids has the new configuration
  centroids = std::move(opt_config);
  curves.clear();

  return minobj;

}
