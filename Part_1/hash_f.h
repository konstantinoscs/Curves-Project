#ifndef HASH_F_H
#define HASH_F_H

class hash_f{
  int id;
  int t;
  std::vector<std::vector<double>> v;
public:
  hash_f(int t_id, int t_t);
  ~hash_f();
  int hash(const std::vector<std::vector<double>> & p, int w);

};
#endif
