#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <string>

class curve{
  std::string id;
  int dimension;
  //every point is a dimensiom-vector of coordinates
  std::vector<std::vector<double>> points;
public:
  curve(int dim = 0);
  ~curve();
  void set_id(std::string r_id)
  std::string get_id();
  int get_dimension();

};

#endif
