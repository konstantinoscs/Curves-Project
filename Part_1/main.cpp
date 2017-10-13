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
  vector<real_curve> curves;
  vector<double> t;

  //initialize all parameters
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash);

  data_s = "trajectories_dataset_";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
  }

  // cout << data_s << endl << query_s << endl << out_s << endl;
  // cout << func << endl << hash << endl;

  //minimum of curve points
  int minm{2};
  float r{0.2};
  delta = 4*dimension*minm*r;
  //int-->curve (what does that mean?)
  vector<norm_curve> normalized_curves{};

  for(int i=0; i<curves.size(); i++)
    normalized_curves.push_back(curve_reduction(curves[i],delta));

  for(int rep=0; rep<L; rep++){//for L repetitions
    //let's choose a t...

  }

  //here shift the normalized curve k times
  //choose t in [0,delta)
  //for all normalized_curves:curve_shift(v0,t,v1)
  //concatenate the k curves
  //done
}
