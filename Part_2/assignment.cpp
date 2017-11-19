#include <vector>
#include "curve.h"
#include "distance_ops.h"

using namespace std;

int lloyds_assignment(vector<real_curve *> centroids,
  vector<real_curve *> curves, vector<vector<real_curve *>> & assignment){

  int jmin{}, objective{};
  double distmin{}, dist{};

  //we need to access arbitary indexes so ensure that they exist
  if(!assignment.empty())
    assignment.resize(centroids.size());

  for(size_t i=0; i<curves.size(); i++){
    jmin = 0;
    const vector<vector<double>> & c_points = curves[i]->get_points();
    //set as min distance the distance from the first centroid
    computeDFD(c_points, centroids[0]->get_points(), distmin);
    //compare the min with all the other distances
    for (size_t j=1; j<centroids.size(); j++){
      computeDFD(c_points, centroids[j]->get_points(), dist);
      if(dist < distmin){
        distmin = dist;
        jmin = j;
      }
    }
    //assign curve i to centroid jmin
    objective += distmin;
    assignment[jmin].push_back(curves[i]);
  }

  return objective;
}
