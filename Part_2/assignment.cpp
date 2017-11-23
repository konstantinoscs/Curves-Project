#include <vector>
#include <string>

#include "curve.h"
#include "distance_ops.h"

using namespace std;

double lloyds_assignment(vector<real_curve *> & centroids,
  vector<real_curve *> & curves,string dist_func,
  vector<vector<real_curve *>> & assignment){

  int jmin{};
  double distmin{}, dist{}, objective{};

  //we need to access arbitary indexes so ensure that they exist
  if(!assignment.empty())
    assignment.resize(centroids.size());

  for(size_t i=0; i<curves.size(); i++){
    jmin = 0;
    const vector<vector<double>> & c_points = curves[i]->get_points();
    //set as min distance the distance from the first centroid
    find_distance(c_points, centroids[0]->get_points(), dist_func, distmin);
    //compare the min with all the other distances
    for (unsigned int j=1; j<centroids.size(); j++){
      find_distance(c_points, centroids[j]->get_points(), dist_func, dist);
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
