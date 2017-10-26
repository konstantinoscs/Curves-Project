#include <vector>

#include "curve.h"
#include "general_hash.h"
#include "entry.h"

using namespace std;

void classic_curve_hashing(const vector<int> & concat_norm_points, vector<int> & r,
  vector<entry> *ht, int tablesize, vector<real_curve*> & curves,
  int curve_index, vector<real_curve> & normalized_curves){

  int key{};
  entry temp{};

  linear_combination(concat_norm_points,r,key,tablesize);
  temp.rcurve = curves[curve_index];
  temp.gcurve = &normalized_curves[curve_index];
  ht[key].push_back(std::move(temp));
}
