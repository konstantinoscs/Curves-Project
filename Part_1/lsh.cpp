#include <vector>

#include "hash_f.h"

void make_hashes(std::vector<hash_f> & hs, int w, int v_size, int k){
  for(int i =0; i<k; i++)
    hs.push_back(std::move(hash_f(i, w, v_size)));
}
