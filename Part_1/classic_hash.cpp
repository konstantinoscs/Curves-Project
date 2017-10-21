#include <vector>
#include <string>
#include <array>
#include <limits>
#include <iostream>

#include "curve.h"
#include "rand_utils.h"
#include "lsh.h"

using namespace std;

void init_r(int dimension, vector<int> & r){
    for(int i=0; i< dimension; i++)
      r.push_back(int_uniform_rand(0,1000000));//idk the [M,N]
    return ;
}

void linear_combination(const vector<int> & cur_points, const vector<int> & r,
  int & key,int tablesize){

  //largest prime less than 2^{31}-->2^{31}-1
  int M{std::numeric_limits<int>::max() - 5};//M=2^(31)-5
  int factor{0};
  for(int i=0; i<cur_points.size(); i++)
    factor += (cur_points[i]*r[i])%M;
  key = (factor % tablesize + tablesize) % tablesize;
}

void curve_hashing(const vector<int> & concat_norm_points, vector<int> & r,
  vector<vector<real_curve*>> *ht, int tablesize, vector<real_curve*> & curves,
  int curve_index, vector<real_curve> & normalized_curves){

  int key{};
  vector<real_curve*> temp{};

  linear_combination(concat_norm_points,r,key,tablesize);
  temp.push_back(curves[curve_index]);
  temp.push_back(&normalized_curves[curve_index]);
  ht[key].push_back(std::move(temp));
}

void hash_curves(const vector<vector<norm_curve>> & Lcurves,
  int dimension, vector<vector<vector<vector<real_curve*>>>> & Lhashtable,
  int tablesize, vector<real_curve*> & pcurves,
  vector<real_curve> & normalized_curves){

  int L{Lcurves.size()};
  int curve_size{Lcurves[0].size()};
  vector<int> r{};

  for(int i=0; i<L; i++){
    vector<vector<real_curve*>> hashtable[tablesize];
    init_r(dimension,r);

    for(int j=0; j<curve_size; j++){
      curve_hashing(Lcurves[i][j].as_vector(),r, hashtable, tablesize,
      pcurves,j,normalized_curves);
    }

    r.clear();
    vector<vector<vector<real_curve*>>> temp{};

    for(int j=0;j<tablesize;j++){
      temp.push_back(std::move(hashtable[j]));
      hashtable[j].clear();
    }
    //L*L hashtables?
    Lhashtable.push_back(std::move(temp));
    temp.clear();
  }
}

void print_hashtable(vector<vector<vector<real_curve*>>> & ht,
  int tablesize){

  for(int i=0; i<ht.size();i++){
    cout <<"key = "<<i<<": ";
    for(int j=0;j<ht[i].size();j++)
      cout << "-->"<<ht[i][j][0]->get_id()<<" ";
    cout << endl;
  }
  return ;
}
