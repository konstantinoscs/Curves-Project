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

string curve::get_id() const{
  return id;
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
