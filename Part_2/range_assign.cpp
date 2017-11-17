#include <vector>
#include <string>
#include <limits>

#include "curve.h"
#include "assign_entry.h"
#include "curve_ops.h"
#include "general_hash.h"
#include "minmax.h"
#include "distance_ops.h"

using namespace std;

int isCentroid(string id, const vector<real_curve*> & centroids){
  for(unsigned int i=0; i<centroids.size(); i++){
    //if it's centroid will return here something != 0
    if(!id.compare(centroids[i]->get_id()))//id==c[i]->id
      return i+1;//to avoid returning value 0 here
  }
  return 0;
}

void init_assign_entries(vector<assign_entry> & entries,
  vector<real_curve> & curves){
  entries.clear();
  for(unsigned int i=0; i<curves.size(); i++){
    assign_entry entry{};
    entry.rcurve = &curves[i];
    entry.centroid = -1;
    entry.distance = -1;
    entries.push_back(std::move(entry));
  }
}

void init_hashtable(int L, int k, vector<assign_entry> & entries,
  int dimension, double  delta, const vector<real_curve*> & centroids,
  int kvec, int w, const vector<real_curve> & curves, int tablesize,
  vector<vector<vector<assign_entry*>>> &Lht, vector<int> *centroid_keys){

  vector<real_curve> normalized_curves{};//just temporary to call below function 
  vector<vector<norm_curve>> concat_normalized_curves{};
  int max{};
  Lconcatenate_kcurves(k, L ,curves, dimension, delta,
    concat_normalized_curves, max, normalized_curves);

  hash_curves(concat_normalized_curves, dimension*k*max, Lht,
    tablesize, entries, kvec, w, curves, centroids, centroid_keys);

}

double find_R0(const vector<real_curve*> & centroids,string dist){
  double min_dist{std::numeric_limits<int>::max()},min_dist2{};
  for(unsigned int i=0; i<centroids.size()-1; i++){
    for(unsigned int j=i+1; j<centroids.size(); j++){
      find_distance(centroids[i]->get_points(), centroids[j]->get_points(),
        dist, min_dist2);
      min_dist = MYmin(min_dist,min_dist2);
    }
  }
  return min_dist;
}
