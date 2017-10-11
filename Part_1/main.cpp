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
  bool stats{false};
  string data_s{}, query_s{}, out_s{};
  string func{}, hash{};
  //our curves aka the dataset
  list<curve> curves;
  vector<float> t{};

  //initialize all parameters
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash);

  if(!read_dataset_curves(data_s, curves)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
  }

  // cout << data_s << endl << query_s << endl << out_s << endl;
  // cout << func << endl << hash << endl;

  int minm{2};//minimum of curve points
  float r{0.2};
  delta = 4*dimension*minm*r;
  list<int> normalized_curves{};//int-->curve
  for(list<int>::iterator it=real_curves.begin();it!=real_curves.end();it++){
    normalized_curves.push_back(curve_reduction(*it,delta));
  }
  //here start the L loop algorithm

  //here shift the normalized curve k times
  //choose t in [0,delta)
  //for all normalized_curves:curve_shift(v0,t,v1)
  //concatenate the k curves
  //done
}
