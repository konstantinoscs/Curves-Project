#include <vector>

#include"rand_utils.h"

using namespace std;

void random_init(vector<real_curve*> & curves,int k,
      vector<real_curve*> centroid){
  centroid.clear();//just to be sure that it's empty
  int index{};
  for(unsigned int i=0; i<k; i++){
    index = int_uniform_rand(0,curves.size()-1);
    centroid.push_back(curves[index]);
    curve.erase(curve.begin() + index);
  }
  return ;
}

void kmeans_init(vector<real_curve*> & curves,int k,
      vector<real_curve*> & centroid){

}


