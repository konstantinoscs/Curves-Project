#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <string>

class curve{
  std::string id;
  int dimension;
  //every point is a dimension-vector of coordinates
  std::vector<std::vector<double>> points;
public:
  curve(int dim = 0);
  virtual ~curve();
  void set_id(std::string r_id);
  std::string get_id() const;
  int get_dimension() const;
  void set_point(std::vector<double> & point);
  void set_point(std::vector<double> && point);
  const std::vector<std::vector<double>> & get_points() const;
  void print();

};

#endif
