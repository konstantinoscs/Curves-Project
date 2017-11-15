#include <vector>
#include <string>

#include"rand_utils.h"
#include "curve.h"
#include "minmax.h"
#include "distance_ops.h"

using namespace std;

void random_init(vector<real_curve*> & curves,int k,
      vector<real_curve*> & centroid){
  centroid.clear();//just to be sure that it's empty
  int index{};
  for(int i=0; i<k; i++){
    index = int_uniform_rand(0,curves.size()-1);
    centroid.push_back(curves[index]);
    curves.erase(curves.begin() + index);//remove centroid
  }
}

int find_t(vector<double> A,double x,int start,int end){
	int m =start + (end - start)/2;
	if(x==A[start])
		return start;
	else if(x==A[end])
		return end-1;
	else if((start==end) || (end==start+1))
		return end-1;
	else if(A[m] < x)
		return find_t(A,x,m,end);
	else
		return find_t(A,x,start,m);
}

void kmeans_init(vector<real_curve*> & curves,int k,
      vector<real_curve*> & centroid, string dist){
  centroid.clear();
  int index{int_uniform_rand(0,curves.size()-1)};
  centroid.push_back(curves[index]);//first centroid
  curves.erase(curves.begin() + index);//remove 1st centroid
  for(int z=0; z<k-1; z++){//lets find the k-1 remaining centroids
    vector<double> Sum{};
    double temp_min1{},temp_min2{}, new_t{};
    int t{};//centroid's index
    //first rep before loop to find Sum[0];
    find_distance(centroid[0]->get_points(), curves[0]->get_points(),
      dist, temp_min1);
    for(unsigned int j=1; j<centroid.size(); j++){
      find_distance(centroid[j]->get_points(), curves[0]->get_points(),
        dist, temp_min2);
      temp_min1 = MYmin(temp_min1,temp_min2);//keeps the min dist between c
    }
    Sum.push_back(temp_min1*temp_min1);//Sum[0] = d[0]^2
    //rest curves.size()-1 reps...
    for(unsigned int i=0; i<curves.size(); i++){
      find_distance(centroid[0]->get_points(), curves[i]->get_points(),
        dist, temp_min1);
      for(unsigned int j=1; j<centroid.size(); j++){
        find_distance(centroid[j]->get_points(), curves[0]->get_points(),
          dist, temp_min2);
        temp_min1 = MYmin(temp_min1,temp_min2);
      }
      Sum.push_back(Sum[i] + temp_min1*temp_min1);//Sum[i+1] = Sum[i]+d[i+1]^2
    }
    new_t = double_uniform_rand(Sum[Sum.size()-1]);
    t = find_t(Sum, new_t, 0, Sum.size()-1);//finds new centroid's index
    centroid.push_back(curves[t]);//push it here
    curves.erase(curves.begin() + t);//and remove it from here
  }
  return ;
}

