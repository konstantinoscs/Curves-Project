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

void range_assign(vector<real_curve*> & centroids,
  vector<vector<vector<assign_entry*>>> &Lht,
  vector<vector<int>> & keys, string dist){}

void search_in_entries(vector<assign_entry> & entries,
  vector<vector<vector<assign_entry*>>> &Lht,
  vector<vector<int>> & keys, int & flag,
  vector<vector<real_curve*>> & assigned_objects){}

void assign_by_range_search(vector<real_curve*> & centroids,
  vector<vector<vector<assign_entry*>>> &Lht, vector<assign_entry> entries,
  vector<vector<int>> & keys, string dist,
  vector<vector<real_curve*>> & assigned_objects){

}
