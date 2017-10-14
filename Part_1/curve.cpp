#include <iostream>
#include <vector>
#include "curve.h"

using namespace std;

curve::curve(int dim): dimension(dim){
}

curve::curve(curve & c_curve) : id(c_curve.id), dimension(c_curve.dimension),
  points(c_curve.points) {
  //cout << "Copy constructor of curve called!" <<endl;
}

curve::curve(curve && m_curve) : id(m_curve.id), dimension(m_curve.dimension),
  points(std::move(m_curve.points)){
  m_curve.points.clear();
  //cout << "Move constructor of curve called!" <<endl;
}

curve::~curve(){
}

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

void curve::set_point(std::vector<double> & point){
  points.push_back(point);
}

void curve::set_point(std::vector<double> && point){
  points.push_back(point);
}

const std::vector<std::vector<double>> & curve::get_points() const{
  return points;
}

void curve::print(){
  cout << "Curve " << get_id() << endl;
  cout << "Points: " << endl;
  // cout << "(";
  // for(int j=0; j<points[0].size(); j++){
  //   cout << points[0][j] << " ";
  // }
  // cout << "), ";

  for(unsigned int i=0; i<points.size(); i++){
    cout << "(";
    for(unsigned int j=0; j<points[i].size(); j++){
      cout << points[i][j] << " ";
    }
    cout << "), ";
  }
  cout << endl << endl;
}
