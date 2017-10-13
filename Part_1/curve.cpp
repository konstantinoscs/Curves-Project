#include <iostream>
#include <vector>
#include "curve.h"

using namespace std;

curve::curve(int dim): dimension(dim){
  cout << "Default constructor for curve called" << endl;
}

curve::~curve(){

}

void curve::set_id(string r_id){
    id = r_id;
}

string curve::get_id(){
  return id;
}

int curve::get_dimension(){
  return dimension;
}

real_curve::real_curve(){

}

real_curve::~real_curve(){

}

void real_curve::set_point(std::vector<double> & point){
  points.push_back(point);
}

void real_curve::set_point(std::vector<double> && point){
  points.push_back(point);
}

const std::vector<std::vector<double>> & real_curve::get_points(){
  return points;
}

can_curve::can_curve(){

}

can_curve::~can_curve(){

}

void can_curve::set_point(std::vector<int> & point){
  points.push_back(point);
}

void can_curve::set_point(std::vector<int> && point){
  points.push_back(point);
}

const std::vector<std::vector<int>> & can_curve::get_points(){
  return points;
}
