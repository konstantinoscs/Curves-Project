#include <vector>

#include "curve.h"
#include "assign_entry.h"

using namespace std;

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

void init_hashtable(int L, int k, const vector<assign_entry> & entries,
  int dimension, double  delta, const vector<real_curve*> & centroids,
  int kvec, int w, const vector<real_curve> & curves,
  vector<vector<vector<assign_entry*>>> &Lht, int** centroid_keys){
  

}
