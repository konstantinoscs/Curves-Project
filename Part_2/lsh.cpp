#include <vector>

#include "hash_f.h"
#include "general_hash.h"
#include "rand_utils.h"
#include "assign_entry.h"
#include "range_assign.h"

using namespace std;

//makes kvec hash functions and puts them in hs
void make_hashes(vector<hash_f> & hs, int w, int v_size, int kvec){
  //we use the constructor that picks the t so we don't have to
  //provide it
  for(int i =0; i<kvec; i++)
    hs.push_back(std::move(hash_f(i, w, v_size)));
}

//choose kvec h_i randomly, the indexes of the hash functions are
//put in an int vector g
//g and hs have the same size!
void make_g(const vector<hash_f> & hs, vector<int> & g){
  for(size_t i=0; i<hs.size(); i++)
    g.push_back(int_uniform_rand(0, hs.size()-1));
}

void lsh_curve_hashing(const vector<int> & concat_norm_points,
  const vector<int> & r, vector<assign_entry*> *ht, int tablesize,
  int curve_index, vector<assign_entry> & entries, vector<int> & g,
  vector<hash_f> & hs, const vector<real_curve> & curves,
  const vector<real_curve*> & centroids, vector<int> * centroid_keys){

  int key{};
  //assign_entry* temp{};
  vector<int> h_results;

  //remember: g and hs have the same size!
  for (size_t i=0; i<g.size(); i++){
    h_results.push_back(hs[g[i]].hash(concat_norm_points));
  }
  //compute the linear_combination of h and r
  linear_combination(h_results,r,key,tablesize);
  //check if its centroid then save the key
  int isC = isCentroid(curves[curve_index].get_id(),centroids);
  if(isC){
    centroid_keys[isC-1].push_back(key);
    return ;
  }
  ht[key].push_back(&entries[curve_index]);
}
