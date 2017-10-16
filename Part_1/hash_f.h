#ifndef HASH_F_H
#define HASH_F_H

#include <vector>

class hash_f{
  int id;
  int t;
  //v has coordinates according to normal distribution
  std::vector<int> v;
  
  void populate_v();
public:
  hash_f(int t_id, int t_t);
  ~hash_f();
  int hash(const std::vector<int> & p, int w);

};
#endif
