
#include "hash_f.h"

hash_f::hash_f(int t_id, int t_t) : t(t_t), id(t_id){
  //initialize the v
  populate_v();
}

hash_f::~hash_f(){
}

int hash_f::hash(const std::vector<int> & p, int w){
  int sum{} //maybe long double??
  for(int i=0; i<.size(); i++){
    sum += v[i]*p[i];
  }
  return floor((float)(sum+t) / w);
}

hash_f::populate_v(){
  
}
