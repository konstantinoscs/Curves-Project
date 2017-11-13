#include <vector>

#include"rand_utils.h"

using namespace std;

void random_init(const vector<real_curve*> & curves,int k,
      vector<real_curve*> & centroid){
  centroid.clear()//just to be sure that it's empty
  for(unsigned int i=0; i<k; i++)
    centroid.push_back(curves[int_uniform_rand(0,curves.size()-1)]);
  return ;
}

void kmeans_init(const vector<real_curve*> & curves,int k,
      vector<real_curve*> & centroid){

}


