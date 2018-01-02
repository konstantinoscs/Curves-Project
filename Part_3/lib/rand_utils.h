#ifndef RAND_UTILS_H
#define RAND_UTILS_H

//returns double uniform random in [A,B]
double double_uniform_rand(double A, double B);

//returns int uniform random in [A,B]
int int_uniform_rand(int A, int B);

//returns double uniform random in [0,B]
double double_uniform_rand(double B);

//returns double standard normal random
double marsaglia_normal_rand();

#endif
