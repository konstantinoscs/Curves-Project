#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

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
  vector<curve> curves{};
  vector<double> t{};

  //initialize all parameters
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash);

  //data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;

  return 1;

  // cout << data_s << endl << query_s << endl << out_s << endl;
  // cout << func << endl << hash << endl;

  //minimum of curve points
  int minm{2};
  float r{0.2};
  delta = 4*dimension*minm*r;
  
  vector<norm_curve> normalized_curves{};

  for(unsigned int i=0; i<curves.size(); i++)
    normalized_curves.push_back(curve_reduction(curves.at(i),delta));

/*  for(int Lrep=0; Lrep<L; Lrep++){//for L repetitions
    vector<curve> concat_curve_points{};
    for(unsigned int i=0; i<normalized_curves.size(); i++){

    }
    for(int krep=0; krep<k; krep++){
      //let's choose a t...
      t = choosen_t(delta,dimension);
      for(unsigned int i=0; i<normalized_curves.size(); i++)//for every norm curve...
        vector<double> moved_points = curve_move(normalized_curves.at(i),t);
        vector<int> int_curve = curve_d_to_i(moved_c,delta,t);
        concat_curve(int_curve,concat_curve_points.at(i));
    }

  }*/
}
