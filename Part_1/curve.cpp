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

void real_curve::print(){
  cout << "Curve " << get_id() << endl;
  cout << "Points: " << endl;
  // cout << "(";
  // for(int j=0; j<points[0].size(); j++){
  //   cout << points[0][j] << " ";
  // }
  // cout << "), ";

  for(int i=0; i<points.size(); i++){
    cout << "(";
    for(int j=0; j<points[i].size(); j++){
      cout << points[i][j] << " ";
    }
    cout << "), ";
  }
  cout << endl << endl;
}

norm_curve::norm_curve(){

}

norm_curve::~norm_curve(){

}

void norm_curve::set_point(std::vector<int> & point){
  points.push_back(point);
}

void norm_curve::set_point(std::vector<int> && point){
  points.push_back(point);
}

const std::vector<std::vector<int>> & norm_curve::get_points(){
  return points;
}

void norm_curve::print(){
  cout << "Curve " << get_id() << endl;
  cout << "Points: " << endl;
  for(int i=0; i<points.size(); i++){
    cout << "(";
    for(int j=0; j<points[i].size(); j++){
      cout << points[i][j] << " ";
    }
    cout << "), ";
  }
  cout << endl << endl;
}
