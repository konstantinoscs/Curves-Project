#include <string>
#include <cstdlib>
#include "curve.h"
#include <cmath>

using namespace std;

curve curve_reduction(const curve & ur_curve, float delta){
  //ur_curve --> unreducted curve
  //curve cur = new curve(ur_curve.get_dimension());
  //cur.set_id(ur_curve.get_id());
  //vector<vector<double>> points = ur_curve.get_points();
  vector<vector<double>> new_points;
  float element{};
  float p{delta/2};
  int negative_bit{};
  float current_p{};

  // for(unsigned int i=0; i<points.size(); i++){
  //   vector<double> point_coordinates{};
  //   for(unsigned int j=0; j<(points.at(i)).size(); j++){
  //     negative_bit = 1;
  //     cur_c_p = (points.at(i)).at(j);//current coordinate of point
  //     if(cur_c_p != abs(cur_c_p))
  //       negative_bit = -1;
  //     //element = (x + d/2)/d
  //     element = floor((negative_bit*cur_c_p + p)/delta);//n_b*curcp==abs(curcp)
  //     point_coordinates.push_back(element*delta*negative_bit);
  //   }
  //   new_points.push_back(point_coordinates);
  // }
  // cur.set_points(new_points);
  // return cur;
}
