#include <cstdlib>
#include <cmath>

//uniform random in [A,B]
double get_uniform_rand(double A, double B){
  //+1.0 implicitly converts to float division
  return B + (rand() / (RAND_MAX + 1.0)) * (B - A + 1);
}

double get_uniform_rand(double B){
  return get_uniform_rand(0, B);
}

//normal random in [A,B]
double marsaglia_normal_rand(){
  double u{}, v{}, x{}, s{2};
  while (s>=1){
    u = get_uniform_rand(-1, 1);
    v = get_uniform_rand(-1, 1);
    s = u*u + v*v;
  }
  x = u * sqrt(-2*log(s)/s);
  return x;
}
