#ifndef HASH_F_H
#define HASH_F_H

#include <vector>

class hash_f{
  int id;
  float t;
  int w;
  //v has coordinates according to normal distribution
  std::vector<float> v;

  void populate_v(int v_size);
public:
  //you can give a t or t is chosen at construction
  hash_f(int t_id, int t_w, int v_size);
  hash_f(int t_id, float t_t, int t_w, int v_size);
  hash_f(const hash_f & c_hash);
  hash_f(hash_f && m_hash);
  ~hash_f();
  int hash(const std::vector<int> & p);
  void print();

};
#endif
