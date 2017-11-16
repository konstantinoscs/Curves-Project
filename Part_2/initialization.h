#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <vector>
#include <string>

#include "curve.h"

<<<<<<< HEAD
void random_init(std::vector<real_curve*> & curves, int k, std::vector<real_curve*> & centroid);

void kmeans_init(std::vector<real_curve*> & curves, int k, std::vector<real_curve*> & centroid);
=======
void random_init(
  std::vector<real_curve*> & curves,//start:has all curves,end:without the k centroids
  int k,//number of centroids
  std::vector<real_curve*> & centroid);//in the end has the k centroids

//same with above function
void kmeans_init(std::vector<real_curve*> & curves,int k,
       std::vector<real_curve*> & centroid, std::string dist);

//A is a sorted array
//returns the A's index which has the min value bigger than x
int find_t(std::vector<double> A,double x,int start,int end);
>>>>>>> 5174deaa7adc25ef6c96a0ce698ae3b8c387b4c0

#endif
