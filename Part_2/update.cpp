#include <vector>
#include <utility>
#include <string>
#include <limits>
#include <iostream>

#include "curve.h"
#include "distance_ops.h"
#include "mean_curves.h"

using namespace std;

double compute_objective(real_curve* centroid,
  vector<real_curve *> & assignment, string func);

//double compute_objective(vector<real_curve *> & centroids,
//  vector<vector<real_curve *>> & assignment, string func);

real_curve * cluster_centroid(vector<real_curve *> & cluster){
  vector<real_curve *> means;
  //compute centroids from the dataset curves (bottom leaf level)
  for(size_t i=0; i<cluster.size(); i+=2){
    if(i+1<cluster.size())
      means.push_back(find_mean(cluster[i], cluster[i+1]));
    else
      means.push_back(cluster[i]);
  }
  //start the reduction until you get to the root
  while(means.size()>1){
    vector<real_curve *> temp_means;
    for(size_t i=0; i<means.size(); i+=2){
      if(i+1<means.size()){
        temp_means.push_back(find_mean(means[i], means[i+1]));
        //check if the curves were temporary means and delete them
        //(in the case of odd number of curves one leaf will be part
        // of the original dataset so don't delete it)
        if(!means[i]->get_id().compare("-1"))
          delete means[i];
        if(!means[i+1]->get_id().compare("-1"))
          delete means[i+1];

      }
      else
        temp_means.push_back(means[i]);

    }
    means = std::move(temp_means);
  }

  return means.back();
}

bool mean_discrete_frechet(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment){

  vector<real_curve *> temp_centroids;
  //find which centroids were mean curves (not in dataset) and
  //delete them
  for(size_t i=0; i<centroids.size(); i++){
    if(!centroids[i]->get_id().compare("-1"))
      delete centroids[i];
    centroids[i] = nullptr;
  }
  //for each cluster compute the new centroid
  for(size_t i=0; i<centroids.size(); i++)
    centroids[i] = cluster_centroid(assignment[i]);

  return true;
}

double pam_update(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment, double objective, string func){

  double obj{}, minobj{};
  vector<real_curve *> opt_config{};
  opt_config.resize(centroids.size());
  //real_curve * temp{nullptr};

  //start swapping every centroid
  for(size_t i=0; i<centroids.size(); i++){
    minobj = std::numeric_limits<double>::max();
    //swap centroid with every curve in the current cluster to find medoid
      for(size_t j=0; j<assignment[i].size(); j++){
        //"swap" centroid
        centroids[i] = assignment[i][j];
        //compute objective
        obj = compute_objective(centroids[i], assignment[i], func);
        //here every
        if(obj < minobj){
          minobj = obj;
          opt_config[i] = centroids[i];
        }
      }
    }
  //now centroids has the new configuration
  centroids = std::move(opt_config);
  return minobj;
}

double compute_objective(real_curve* centroid,
  vector<real_curve *> & assignment, string func){

  double dist{},objective{};
  for(unsigned int i=0; i<assignment.size(); i++){
    find_distance(centroid->get_points(), assignment[i]->get_points(), func, dist);
    objective += dist;
  }
  return objective;
}
/*double compute_objective(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment, string func){

  double objective{}, dist{};

  for(size_t i=0; i<centroids.size(); i++){
    //get centroid points
    const vector<vector<double>> & c_points = centroids[i]->get_points();
    //for every curve in cluster add distance to centroid
    for(size_t j=0; j<assignment[i].size(); j++)
    find_distance(c_points, assignment[i][j]->get_points(), func, dist);
    objective += dist;
  }
  return objective;
}*/
