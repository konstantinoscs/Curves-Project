#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>
#include <ctime>

#include "data_ops.h"
#include "curve.h"
#include "curve_ops.h"
#include "hash_f.h"
#include "classic_hash.h"
#include "lsh.h"

using namespace std;


int main(int argc, char **argv){
  //k = locality sensitive functions
  //L  = number of hashtables
  //w = window for the hs
  int k{4}, L{5}, w{4};
  double delta{};
  int dimension{}, v_size{};
  bool stats{false};
  string data_s, query_s, out_s;
  string func, hash;
  //our curves aka the dataset
  vector<real_curve> curves;
  vector<vector<norm_curve>> concat_normalized_curves{};
  vector<hash_f> hs;
  cout << std::fixed;
  cout << std::setprecision(17);
  srand(time(0));

  //initialize all parameters
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash);

  //data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;
  // for(int i=0; i<2; i++){
  //   cout << "Printing some curves!" << endl;
  //   curves[i].print();
  // }

  //return 1;

  // cout << data_s << endl << query_s << endl << out_s << endl;
  // cout << func << endl << hash << endl;

  //delta = 4*dimension*minm*r; (should be like that)
  delta = 0.05;
  //cout <<"For delta = "<<delta <<endl;

  /*Lconcatenate_kcurves will end with concat_normalized_curves having
  L vectors of */
  Lconcatenate_kcurves(k, L ,curves, dimension, delta, concat_normalized_curves, v_size);

  //u got it
  //make_hashes(hs, w, v_size, k);
  //hs[1].print();

  //concat_normalized_curves[0][0].print();
  int table_size = curves.size()/4;
  //L arrays of vectors of pointers(to real curves)
  vector<vector<vector<real_curve*>>> Lhashtable;
  //if(hash=="Classic")
      classic_hash_curves(concat_normalized_curves,
        dimension*k*v_size,Lhashtable,table_size,curves);
  //L = concat_normalized_curves.size()
  //else
  //  lsh_hash_curves(concat_normalized_curves,w,v_size,k);

  cout << "End" << endl;
  return 1;
}
