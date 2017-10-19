#include <vector>
#include <string>
#include "curve.h"

void search_curves(std::vector<real_curve> & s_curves,
  std::vector<std::vector<std::vector<std::vector<real_curve*>>>> & Lht,
  int k, int v_size, int dimension, int delta, int tablesize,
  std::string hash);
