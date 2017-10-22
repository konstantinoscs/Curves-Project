#include <vector>
#include <new>

#include "hash_f.h"
#include "classic_hash.h"
#include "rand_utils.h"

using namespace std;

//makes k hash functions and puts them in hs
void make_hashes(vector<hash_f> & hs, int w, int v_size, int k){
  for(int i =0; i<k; i++)
    hs.push_back(std::move(hash_f(i, w, v_size)));
}

//choose k h_i randomly, the indexes of the hash functions are
//put in an int array g
void make_g(const vector<hash_f> & hs, int * g){
  for(int i=0; i<hs.size(); i++)
    g[i] = int_uniform_rand(0, hs.size()-1);
}

//the lsh hashing, most probably will be omitted and integrated in
//hash_curves of "classic_hash.cpp"
void lsh_hash_curves(int k, int w, int v_size, int dimension, int tablesize,
  const vector<vector<norm_curve>> & Lcurves){

  int * g = new int[k];
  vector<hash_f> hs;
  vector<int> r{};

  make_hashes(hs, w, v_size, k);
  init_r(dimension, r);
}
