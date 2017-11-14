#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include<vector>

#include "curve.h"

void random_init(std::vector<real_curve*> & curves,int k,std::vector<real_curve*> & centroid);

void kmeans_init(std::vector<real_curve*> & curves,int k,std::vector<real_curve*> & centroid);

#endif
