#include <string>
#include <cstdlib>
#include "curve.h"
#include <cmath>

using namespace std;

curve curve_reduction(const curve & ur_curve, float delta){
  //ur_curve --> unreducted curve
  curve *cur = new curve(ur_curve.curve::get_dimension());
  cur->curve::set_id(ur_curve.curve::get_id());
  vector<vector<double>> points = ur_curve.get_points();
  double element{};
  double p{delta/2};
  int negative_bit{};
  double cur_c_p{};

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
    cur->curve::set_point(point_coordinates);
  }
  return *cur;
}
