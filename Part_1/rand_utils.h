#ifndef RAND_UTILS_H
#define RAND_UTILS_H

//uniform random in [A,B]
double get_uniform_rand(double A, double B);

//uniform random in [0,B]
double get_uniform_rand(double B);

//standard normal random
double marsaglia_normal_rand();

#endif
