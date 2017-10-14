#include <string>
#include <cstdlib>
#include "curve.h"
#include <cmath>

using namespace std;

real_curve curve_reduction(const real_curve & ur_curve, double delta){
  //ur_curve --> unreducted curve
  real_curve cur(ur_curve.get_dimension());
  cur.set_id(ur_curve.get_id());
  vector<vector<double>> points = ur_curve.get_points();
  double element{};
  double p{delta/2};
  int negative_bit{};
  double cur_c_p{};
  vector<double> point_duplicate{};

  for(unsigned int i=0; i<points.size(); i++){
    vector<double> point_coordinates{};
    for(unsigned int j=0; j<(points[i]).size(); j++){
      negative_bit = 1;
      cur_c_p = points[i][j];//current coordinate of point
      if(cur_c_p != abs(cur_c_p))
        negative_bit = -1;
      //element = (x + d/2)/d
      element = floor((negative_bit*cur_c_p + p)/delta);//n_b*curcp==abs(curcp)
      point_coordinates.push_back(element*delta*negative_bit);
    }
    //check for consecutive duplicates
    if(point_coordinates!=point_duplicate){//push the new point only if
      point_duplicate = point_coordinates;//if its different from
      cur.set_point(std::move(point_coordinates));// the last one
    }
  }
  return cur;
}

void chosen_t(double delta, int dimension, vector<double> & t){
  int randomn{};
  double coordinate{};
  for(int i=0; i<dimension; i++){
    randomn = rand()%1000;
    coordinate = (randomn/1000.0)*delta;
    t.push_back(coordinate);
  }
  return ;
}

void curve_move(const vector<vector<double>> & norm_points,
    const vector<double> & t, const int & max, const double & delta,
    const int & dimension, vector<vector<int>> & moved_points){
  vector<int> pointvec{};
  int ipoint{};
  double dpoint{};
  vector<vector<int>>::iterator iter{};
  int mysize{};
  mysize = norm_points.size();
  vector<int> zero{};
  for(int i=0;i<dimension;i++)
    zero.push_back(0);
  for(unsigned int i=0; i<norm_points.size(); i++){
    for(unsigned int j=0; j<norm_points[i].size(); j++){
      dpoint = norm_points[i][j] + t[j];
      ipoint = int((dpoint +delta/2.0)/delta);
      pointvec.push_back(ipoint);
    }
    moved_points.push_back(std::move(pointvec));
    pointvec.clear();
  }
  for(int i=0;i<int((max-mysize)/2);i++){
    iter = moved_points.begin();
    moved_points.insert(iter,zero);
  }
  for (int i=0;i<int((max-mysize+1)/2);i++)
    moved_points.push_back(zero);
  return ;
}
