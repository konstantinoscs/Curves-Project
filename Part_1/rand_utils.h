#ifndef RAND_UTILS_H
#define RAND_UTILS_H

//uniform random in [A,B]
double double_uniform_rand(double A, double B);

//int uniform random in [A,B]
int int_uniform_rand(int A, int B);

//uniform random in [0,B]
double double_uniform_rand(double B);

//standard normal random
double marsaglia_normal_rand();

#endif
