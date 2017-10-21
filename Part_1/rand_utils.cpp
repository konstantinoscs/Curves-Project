#include <cstdlib>
#include <cmath>

//uniform random in [A,B]
double double_uniform_rand(double A, double B){
  //+1.0 implicitly converts to float division
  return A + (rand() / (RAND_MAX + 1.0)) * (B - A);
}

int int_uniform_rand(int A, int B){
  return A + (rand() / (RAND_MAX + 1.0)) * (B - A + 1);
}

double double_uniform_rand(double B){
  return double_uniform_rand(0.0, B);
}

//normal random in [A,B]
double marsaglia_normal_rand(){
  double u{}, v{}, x{}, s{2};
  while (s>=1){
    u = double_uniform_rand(-1.0, 1.0);
    v = double_uniform_rand(-1.0, 1.0);
    s = u*u + v*v;
  }
  x = u * sqrt(-2*log(s)/s);
  return x;
}
