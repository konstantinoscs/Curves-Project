#include <cmath>
#include "hash_f.h"
#include "rand_utils.h"

//chose t at construction
hash_f::hash_f(int t_id, int t_w, int v_size) : id(t_id), w(t_w){
  t = get_uniform_rand(w);
  populate_v(v_size);
}

//give your own t
hash_f::hash_f(int t_id, float t_t, int t_w, int v_size) : t(t_t), w(t_w),
id(t_id){
  //initialize the v
  populate_v(v_size);
}

hash_f::~hash_f(){
}

int hash_f::hash(const std::vector<int> & p){
  float sum{};
  for(int i=0; i<v.size(); i++){
    sum += v[i]*p[i];
  }
  //(float) is necessary here
  return floor((float)(sum+t) / w);
}

void hash_f::populate_v(int v_size){
  for(int i=0; i<v_size; i++)
    v.push_back(marsaglia_normal_rand());
}
