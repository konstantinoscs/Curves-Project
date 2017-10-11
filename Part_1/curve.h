#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <string>

class curve{
  std::string id;
  int dimension;
  std::vector<std::vector<float>> points;
public:
  curve(std::string c_id, int dim = 0);
  ~curve();
  std::string get_id();
  int get_dimension();
};

#endif
