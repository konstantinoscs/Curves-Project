#include <string>
#include <vector>
#include <limits>

#include "minmax.h"
#include "curve.h"
#include "update.h"
#include "distance_ops.h"

using namespace std;

int find_second_best(real_curve * tempC, int y,
  vector<real_curve*> & centroids, string dist){

  double min_dist{std::numeric_limits<int>::max()},min_dist2;
  int index{};
  for(unsigned int i=0; i<centroids.size(); i++){
    if((int)i==y) continue;//don't check it's real centroid
    find_distance(tempC->get_points(), centroids[i]->get_points(),
      dist, min_dist2);
    if(min_dist>min_dist2){
      min_dist = min_dist2;
      index = i;
    }
  }
  return index;
}

void compute_silhuette(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment, string dist,
  vector<double> & Si, double & Stotal){

  Si.clear();
  if(centroids.size()==1){
    Si.push_back(1);//in case we have one cluster silhuette=1
    return ;
  }
  Stotal = 0.0;
  double objA, objB, clusterS;
  int sec_best;
  for(unsigned int i=0; i<centroids.size(); i++){
    clusterS = 0.0;
    for(unsigned int j=0; j<assignment[i].size(); j++){
      objA = compute_objective(assignment[i][j], assignment[i], dist);
      sec_best = find_second_best(assignment[i][j], i, centroids, dist);
      objB = compute_objective(assignment[i][j], assignment[sec_best], dist);
      clusterS += (objB - objA)/MYmax(objA,objB);
    }
    Si.push_back(clusterS);
    Stotal += clusterS;
  }
}
