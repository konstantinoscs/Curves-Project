#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "data_ops.h"
#include "curve.h"
#include "curve_ops.h"

using namespace std;


int main(int argc, char **argv){
  //k = locality sensitive functions
  //L  = number of hasthables
  int k{4}, L{5};
  double delta{};
  int dimension{};
  bool stats{false};
  string data_s, query_s, out_s;
  string func, hash;
  //our curves aka the dataset
  vector<real_curve> curves;
  vector<double> t;
  std::cout << std::fixed;
  cout << std::setprecision(15);

  //initialize all parameters
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash);

  //data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;
  for(int i=0; i<2; i++){
    cout << "Printing some curves!" << endl;
    curves[i].print();
  }

  return 1;

  // cout << data_s << endl << query_s << endl << out_s << endl;
  // cout << func << endl << hash << endl;

  //minimum of curve points
  int minm{2};
  float r{0.2};
  delta = 4*dimension*minm*r;

  vector<real_curve> normalized_curves{};

  for(unsigned int i=0; i<curves.size(); i++){
    normalized_curves.push_back(curve_reduction(curves[i],delta));
    //missing:check for duplicates here
  }

  for(int Lrep=0; Lrep<L; Lrep++){//for L repetitions
    vector<real_curve> concat_curve_points{};
    for(unsigned int i=0; i<normalized_curves.size(); i++){//init concat_curve_points
      real_curve *moved_curve = new real_curve(normalized_curves[i].curve::get_dimension());
      moved_curve->curve::set_id(normalized_curves[i].curve::get_id());
      concat_curve_points.push_back(*moved_curve);
    }
    for(int krep=0; krep<k; krep++){
      //let's choose a t...
      chosen_t(delta,dimension,t);
      for(unsigned int i=0; i<normalized_curves.size(); i++){//for every norm curve...
        vector<vector<double>> moved_points{};
        curve_move(normalized_curves[i].real_curve::get_points(), t, moved_points);
        for(unsigned int j=0; j<moved_points.size(); j++){
          concat_curve_points[i].real_curve::set_point(moved_points[j]);
        }
      }
    }

  }
}
