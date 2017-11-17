#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "curve.h"
#include "rand_utils.h"
#include "assign_entry.h"
#include "lsh.h"

using namespace std;

void init_r(int dimension, vector<int> & r){
    for(int i=0; i< dimension; i++)
      r.push_back(int_uniform_rand(0,1000000));//the selected [M,N] was random
    return ;
}

void linear_combination(const vector<int> & cur_points, const vector<int> & r,
  int & key,int tablesize){

  //largest prime less than 2^{31}-->2^{31}-1
  int M{std::numeric_limits<int>::max()};//M=2^(31)-1
  int factor{0};
  for(size_t i=0; i<cur_points.size(); i++)
    factor += (cur_points[i]*r[i])%M;
  key = (factor % tablesize + tablesize) % tablesize;
}

void hash_curves(const vector<vector<norm_curve>> & Lcurves,
  int dimension, vector<vector<vector<assign_entry*>>> & Lhashtable,
  int tablesize, vector<assign_entry> & entries, int kvec, int w,
  const vector<real_curve> & curves, const vector<real_curve*> & centroids,
  vector<int> * centroid_keys){

  size_t L{Lcurves.size()};
  size_t curve_size{Lcurves[0].size()};
  vector<int> r{};


  for(size_t i=0; i<L; i++){
    vector<assign_entry*> hashtable[tablesize];

    //always hash=="probabilistic"
    init_r(kvec, r);
    vector<hash_f> hs;
    vector<int> g;
    make_hashes(hs, w, dimension, kvec);
    make_g(hs, g);
    for(size_t j=0; j<curve_size; j++)
      lsh_curve_hashing(Lcurves[i][j].as_vector(),r, hashtable,
        tablesize, j, entries, g, hs, curves, centroids, centroid_keys);

    r.clear();
    vector<vector<assign_entry*>> temp{};

    for(int j=0;j<tablesize;j++){
      temp.push_back(std::move(hashtable[j]));
      hashtable[j].clear();
    }
    Lhashtable.push_back(std::move(temp));
    temp.clear();
  }
}

