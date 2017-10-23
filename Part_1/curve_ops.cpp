#include <string>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iostream>

#include "curve.h"
#include "rand_utils.h"

using namespace std;

void curve_reduction(const real_curve & ur_curve, double delta,
    real_curve & cur, int & min, int & max){
  //ur_curve --> unreducted curve
  vector<vector<double>> points = ur_curve.get_points();
  double element{};
  double p{delta/2.0};
  int negative_bit{};
  int point_counter{0};
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
      point_counter++;
    }
  }
  if(point_counter>max)
    max = point_counter;
  else if(point_counter<min)
    min = point_counter;
}

void chosen_t(double delta, int dimension, vector<double> & t){
  for(int i=0; i<dimension; i++)
    t.push_back(double_uniform_rand(delta));
  return ;
}

void curve_move(const vector<vector<double>> & norm_points,
    const vector<double> & t, int max, double delta,
    int dimension,int k,vector<vector<int>> &moved_points){
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
      ipoint = int((dpoint +(delta/k)/2.0)/(delta/k));
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

void Lconcatenate_kcurves(int k, int L,
  const vector<real_curve> & curves, int dimension, double  delta,
  vector<vector< norm_curve >> & concat_normalized_curves, int & max,
  vector<real_curve> & normalized_curves){

    vector<double> t{};
    int min{std::numeric_limits<int>::max()};
    max = 0;

    for(unsigned int i=0; i<curves.size(); i++){
      real_curve grid_cur(curves[i].get_dimension());
      grid_cur.set_id(curves[i].get_id());
      curve_reduction(curves[i],delta,grid_cur,min,max);
      normalized_curves.push_back(std::move(grid_cur));
    }
    //cout <<"max="<<max<<"\nmin="<<min<<endl;

    for(int Lrep=0; Lrep<L; Lrep++){//for L repetitions
      vector<norm_curve> concat_curves{};
      for(unsigned int i=0; i<normalized_curves.size(); i++){//init concat_curve_points
        norm_curve moved_curve(normalized_curves[i].get_dimension());
        moved_curve.set_id(normalized_curves[i].get_id());
        concat_curves.push_back(std::move(moved_curve));
      }
      for(int krep=0; krep<k; krep++){
        t.clear();
        //let's choose a t...
        chosen_t(delta,dimension,t);
        //cout << "t= (";
        //for(int i=0;i<dimension;i++){
        //  cout <<t[i] << " ";
        //}
        //cout <<")"<<'\n';
        for(unsigned int i=0; i<normalized_curves.size(); i++){//for every norm curve...
          vector<vector<int>> moved_points{};
          curve_move(normalized_curves[i].get_points(), t, max, delta,
            dimension, k, moved_points);
          for(unsigned int j=0; j<moved_points.size(); j++){
            concat_curves[i].set_point(std::move(moved_points[j]));
            moved_points[j].clear();
          }
        }
      }
      concat_normalized_curves.push_back(std::move(concat_curves));
      concat_curves.clear();
    }

  }
