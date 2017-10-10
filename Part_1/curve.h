#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <string>

class curve{
  std::string id;
  int dimension;
  std::vector<std::vector<float>> points;
public:
  curve(int dim = 0);
  ~curve();
};

#endif
