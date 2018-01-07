#include <iostream>
#include <vector>
#include "curve.h"

using namespace std;

curve::curve(int dim): dimension(dim){
}

curve::curve(const curve &) = default;

curve::curve(curve &&) = default;

curve::~curve() = default;

void curve::set_id(string r_id){
    id = r_id;
}

string curve::get_id() const{
  return id;
}

void curve::set_dimension(int dim){
  dimension = dim;
}

int curve::get_dimension() const{
  return dimension;
}

real_curve::real_curve(int dim) :curve(dim){}

real_curve::real_curve(const real_curve &) = default;

real_curve::real_curve(real_curve &&) = default;

real_curve::~real_curve() = default;

void real_curve::set_point(std::vector<double> & point){
  points.push_back(point);
}

void real_curve::set_point(std::vector<double> && point){
  points.push_back(point);
}

const std::vector<std::vector<double>> & real_curve::get_points() const{
  return points;
}

const std::vector<double> real_curve::as_vector() const{
  std::vector<double> v{};
  for(size_t i=0; i<points.size(); i++)
    for(size_t j=0; j<points[i].size(); j++)
      v.push_back(points[i][j]);
  return v;
}

void real_curve::print(){
  cout << "Curve " << get_id() << endl;
  cout << "Points: " << endl;

  for(size_t i=0; i<points.size(); i++){
    cout << "(";
    for(size_t j=0; j<points[i].size(); j++){
      cout << points[i][j] << " ";
    }
    cout << "), ";
  }
  cout << endl << endl;
}

norm_curve::norm_curve(int dim) :curve(dim){}

void norm_curve::set_point(std::vector<int> & point){
  points.push_back(point);
}

void norm_curve::set_point(std::vector<int> && point){
  points.push_back(point);
}

const std::vector<std::vector<int>> & norm_curve::get_points() const{
  return points;
}

const std::vector<int> norm_curve::as_vector() const{
  std::vector<int> v{};
  for(size_t i=0; i<points.size(); i++)
    for(unsigned int j=0; j<points[i].size(); j++)
      v.push_back(points[i][j]);
  return v;
}


void norm_curve::print(){
  cout << "Curve " << get_id() << endl;
  cout << "Points: " << endl;
  for(size_t i=0; i<points.size(); i++){
    cout << "(";
    for(size_t j=0; j<points[i].size(); j++){
      cout << points[i][j] << " ";
    }
    cout << "), ";
  }
  cout << endl << endl;
}

segment::segment(int dim): real_curve(dim){};

void segment::set_way(string && w_id){
  way_id = w_id;
}

string segment::get_way(){
  return way_id;
}
