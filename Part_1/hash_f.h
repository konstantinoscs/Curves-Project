#ifndef HASH_F_H
#define HASH_F_H

#include <vector>

class hash_f{
  int id;
  float t;
  int w;
  //v has coordinates according to normal distribution
  std::vector<float> v;

  void populate_v();
public:
  //you can give a t or t is chosen at construction
  hash_f(int t_id);
  hash_f(int t_id, float t_t);
  ~hash_f();
  int hash(const std::vector<int> & p, int w);

};
#endif
