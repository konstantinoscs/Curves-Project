#include <vector>
#include <string>
#include <array>
#include "curve.h"
#include "rand_utils.h"

using namespace std;

void init_r(int dimension,std::vector<int> & r){
    for(int i=0; i< dimension; i++)
      r.push_back(int_uniform_rand(0,10000));//idk the [M,N]
    return ;
}

void linear_combination(const vector<int> & cur_points, const vector<int> & r,
   int & key){
  return ;
}

void curve_hashing(const norm_curve & cur,vector<int> & r,
    vector<string> *ht, int tablesize){
  return ;
}

void classic_hash_curves(const vector<vector<norm_curve>> & Lcurves,
  int dimension, vector<vector<vector<string>>> Lhashtable,int tablesize){
    int L{};
    L = Lcurves.size();
    int curve_size{};
    curve_size = Lcurves[0].size();
    vector<int> r{};
    vector<string> hashtable[tablesize];
    for(int i=0; i<L; i++){
      init_r(dimension,r);
      for(int j=0; j<curve_size; j++){
        curve_hashing(Lcurves[i][j],r,hashtable,tablesize);
        //linear_combination(,r,key); //used in curve hashing
      }
      r.clear();
      vector<vector<string>> temp{};
      for(int j=0;j<tablesize;j++){
        temp.push_back(std::move(hashtable[j]));
        hashtable[j].clear();
      }
      Lhashtable.push_back(std::move(temp));
      temp.clear();
    }
    return ;
  }
