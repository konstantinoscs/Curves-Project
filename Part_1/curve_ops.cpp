#include <string>
#include <cstdlib>
#include "curve.h"
#include <cmath>

using namespace std;

curve curve_reduction(curve c,float delta){
  curve cur = new curve(c.get_id(),c.get_dimension());
  vector<vector<float>> points = c.get_points();
  vector<vector<float>> new_points{};
  float element;
  float p = delta/2;
  for(int i=0;i<points.size();i++){
    vector<float> point{};
    for(int j=0;j<(points.at(i)).size();j++){
      int negative_bit{0};
      float current_p = (points.at(i)).at(j);
      if(current_p != abs((points.at(i)).at(j)))
        negative_bit = 1;
      element = (((points.at(i)).at(j)) + p)/delta; //element = (x + d/2)/d
      point.push_back(element*delta*negative_bit);
    }
    new_points.push_back(point);
  }
  cur.set_points(new_points);
  return cur;
}
