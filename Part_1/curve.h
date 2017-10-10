#ifndef CURVE_H
#define CURVE_H

#include <vector>

class curve{
  int dimension;
  std::vector<std::vector<float>> points;
public:
  curve();
  ~curve();
};

#endif
