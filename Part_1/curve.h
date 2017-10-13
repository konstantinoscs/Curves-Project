#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include <string>

class curve{
  std::string id;
  int dimension;
  //every point is a dimension-vector of coordinates
  // std::vector<std::vector<double>> points;
public:
  curve(int dim = 0);
  virtual ~curve();
  void set_id(std::string r_id);
  std::string get_id();
  int get_dimension();
  virtual void print() = 0;

};

//real_curve and norm_curve are symmetrical with double and int coordinates
class real_curve : public curve {
  std::vector<std::vector<double>> points;

public:
  real_curve();
  ~real_curve();
  void set_point(std::vector<double> & point);
  //we introduce a move push back
  void set_point(std::vector<double> && point);
  const std::vector<std::vector<double>> & get_points();
  void print();
};

class norm_curve : public curve {
  std::vector<std::vector<int>> points;

public:
  norm_curve();
  ~norm_curve();
  void set_point(std::vector<int> & point);
  //we introduce a move push back
  void set_point(std::vector<int> && point);
  const std::vector<std::vector<int>> & get_points();
  void print();
};

#endif
