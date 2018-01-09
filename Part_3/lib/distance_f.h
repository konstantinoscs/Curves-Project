#ifndef DISTANCE_F_H
#define DISTANCE_F_H

#include<vector>

double pr_cRMSD(std::vector<std::vector<double>> X0,std::vector<std::vector<double>> Y0, int N);

double pr_frechet(std::vector<std::vector<double>> X0,std::vector<std::vector<double>> Y0, int N);

double pr_dtw(std::vector<std::vector<double>> X0,std::vector<std::vector<double>> Y0, int N);

#endif
