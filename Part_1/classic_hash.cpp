#include <vector>
#include "curve.h"
#include "rand_utils.h"

using namespace std;

void init_r(int dimension,std::vector<int> & r){
    for(int i=0; i< dimension; i++)
      r.push_back(int_uniform_rand(-1000,1000));//idk the [M,N]
    return ;
}

void linear_combination(const vector<int> & cur_points, const vector<int> & r,
   int & key){
  return ;
}

void curve_hashing(const norm_curve & cur,vector<int> & r){
  return ;
}

void classic_hash_curves(const vector<vector<norm_curve>> & Lcurves,
  int dimension){
    int L{};
    L = Lcurves.size();
    int curve_size{};
    curve_size = Lcurves[0].size();
    vector<int> r{};
    for(int i=0; i < L; i++){
      init_r(dimension,r);
      for(int j=0; j<curve_size; j++){
        //also has an array[curve_size/4] <--hashtable(arg from ^^)
        curve_hashing(Lcurves[i][j],r);
        //linear_combination(,r,key); //used in curve hashing
      }
      r.clear();
      //push_back the array L times
    }
    return ;
  }
