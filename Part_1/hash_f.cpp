#include <cmath>
#include <iostream>
#include "hash_f.h"
#include "rand_utils.h"

using namespace std;

//chose t at construction
hash_f::hash_f(int t_id, int t_w, int v_size) : id(t_id), w(t_w){
  t = double_uniform_rand(w);
  populate_v(v_size);
}

//give your own t
hash_f::hash_f(int t_id, float t_t, int t_w, int v_size) : id(t_id), t(t_t),
w(t_w){
  //initialize the v
  populate_v(v_size);
}

hash_f::hash_f(const hash_f & c_hash): id(c_hash.id), t(c_hash.t), w(c_hash.w),
  v(c_hash.v){

}

hash_f::hash_f(hash_f && m_hash): id(m_hash.id), t(m_hash.t), w(m_hash.w),
  v(std::move(m_hash.v)){
  m_hash.v.clear();
}

hash_f::~hash_f(){
}

int hash_f::hash(const std::vector<int> & p){
  float sum{};
  for(size_t i=0; i<v.size(); i++){
    sum += v[i]*p[i];
  }
  //(float) is necessary here
  return floor((float)(sum+t) / w);
}

void hash_f::print(){
  cout << "hash_f i with id " << id << endl;
  cout << "t " << t << endl;
  cout << "w " << w << endl;
  cout << "v :" << endl;
  for (size_t i=0; i<v.size(); i++)
    cout << v[i] << endl;;
}

void hash_f::populate_v(int v_size){
  for(int i=0; i<v_size; i++)
    v.push_back(marsaglia_normal_rand());
}
