#include <cstdlib>

//uniform random in [A,B]
double get_rand_uniform(double A, double B){
  return B + (rand() / RAND_MAX + 1)
}

double get_rand_uniform(double B){
  return get_rand_uniform(0, B);
}

//normal random in [A,B]
double get_normal_random(double A, double B){

}
