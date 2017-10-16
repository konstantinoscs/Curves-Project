#ifndef RAND_UTILS_H
#define RAND_UTILS_H

//uniform random in [A,B]
double get_rand_uniform(int A, int B);

//uniform random in [0,B]
double get_rand_uniform(int B);

//normal random in [A,B]
double get_normal_random(int A, int B);

#endif
