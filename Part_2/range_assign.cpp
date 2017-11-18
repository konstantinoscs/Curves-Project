#include <vector>
#include <string>
#include <limits>

#include "curve.h"
#include "assign_entry.h"
#include "minmax.h"
#include "distance_ops.h"
#include "assignment.h"

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

void collect_remaining_objects(vector<assign_entry> & entries,
  vector<real_curve*> & rem_curves){
  rem_curves.clear();
  for(unsigned int i=0; i<entries.size(); i++)
    rem_curves.push_back(entries[i].rcurve);
}

void range_assign(vector<real_curve*> & centroids,
  vector<vector<vector<assign_entry*>>> &Lht, double R,
  vector<vector<int>> & keys, string dist){
  double distance{};
  for(unsigned int i=0; i<Lht.size(); i++){//0<=i<L
    for(unsigned int j=0; j<centroids.size(); j++){//0<=j<c
      for(unsigned int z=0; z<Lht[i][keys[j][i]].size(); z++){//buckets
        find_distance(centroids[j]->get_points(),
          Lht[i][keys[j][i]][z]->rcurve->get_points(),dist,distance);
        if(distance<=R){//then curve in range
          if(Lht[i][keys[j][i]][z]->distance != -1){//if another centroid
            if(Lht[i][keys[j][i]][z]->distance > distance){//found it
              Lht[i][keys[j][i]][z]->distance = distance;//in same range
              Lht[i][keys[j][i]][z]->centroid = j;
            }
          }
          else{//if its the first c which found it...
            Lht[i][keys[j][i]][z]->distance = distance;
            Lht[i][keys[j][i]][z]->centroid = j;
          }
        }
      }
    }
  }
}

void search_in_entries(vector<assign_entry> & entries,
  vector<vector<vector<assign_entry*>>> &Lht,
  vector<vector<int>> & keys, int & flag,
  vector<vector<real_curve*>> & assigned_objects){
  int counter{0};
  //remove assigned curves from hashtable
  for(unsigned int i=0; i<Lht.size(); i++){//0<=i<L
    for(unsigned int j=0; j<keys.size(); j++){//0<=j<c
      for(int z=Lht[i][keys[j][i]].size()-1; z>=0; z--){//buckets
        if(Lht[i][keys[j][i]][z]->centroid != -1){
          counter++;
          Lht[i][keys[j][i]].erase(Lht[i][keys[j][i]].begin() + z);
        }
      }
    }
  }
  //assign curves in assigned_objects
  //and remove them from entries
  for(int i=entries.size()-1; i>=0; i--){
    if(entries[i].centroid != -1){
      assigned_objects[entries[i].centroid].push_back(entries[i].rcurve);
      entries.erase(entries.begin() + i);
      flag = 1;
    }
  }
}

void assign_by_range_search(vector<real_curve*> & centroids,
  vector<vector<vector<assign_entry*>>> Lht, vector<assign_entry> & entries,
  vector<vector<int>> & keys, string dist,
  vector<vector<real_curve*>> & assigned_objects){
  vector<real_curve *> rem_curves{};
  int flag{},final_flag{0};
  double R{};
  R = find_R0(centroids,dist)/2;
  while(final_flag != 2){
    range_assign(centroids,Lht,R,keys,dist);
    flag = 0;
    R *= 2;
    search_in_entries(entries,Lht,keys,flag,assigned_objects);
    if(!flag)//flag == 0
      final_flag++;
  }
  collect_remaining_objects(entries,rem_curves);
  lloyds_assignment(centroids,rem_curves,assigned_objects);
}


