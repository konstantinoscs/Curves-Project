#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>
#include <ctime>

#include "data_ops.h"
#include "search_ops.h"
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
  vector<real_curve> curves{},normalized_curves{};
	vector<real_curve*> pcurves{};
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

	for(int i=0; i<curves.size(); i++)
		pcurves.push_back(&curves[i]);

  /*Lconcatenate_kcurves will end with concat_normalized_curves having
  L vectors of */
  Lconcatenate_kcurves(k, L ,curves, dimension, delta,
    concat_normalized_curves, v_size,normalized_curves);

  //u got it
  //make_hashes(hs, w, v_size, k);
  //hs[1].print();

  //concat_normalized_curves[0][0].print();
  int table_size = curves.size()/16;
  //L arrays of vectors of pointers(to real curves)
  //we need pointers to (1)real curves and (2)normalized curves
  vector<vector<vector<vector<real_curve*>>>> Lhashtable;
  //if(hash=="Classic")
  classic_hash_curves(concat_normalized_curves,
    dimension*k*v_size, Lhashtable, table_size, pcurves,
    normalized_curves);
  //L = concat_normalized_curves.size()
  //else
  //  lsh_hash_curves(concat_normalized_curves,w,v_size,k);

  //print_hashtable(Lhashtable[0],table_size);

  real_curve s0{curves[10]};//only for testing
  s0.set_id("12345");
  vector<real_curve> s_curves{};
  s_curves.push_back(std::move(s0));
  
  vector<real_curve*> nn_curve{};
  vector<double> nn_distance{};
  vector<bool> grid_curve_found{};
  search_curves(s_curves, Lhashtable, k, 0, dimension, delta, table_size,
  	hash, func, pcurves, nn_curve, nn_distance, grid_curve_found);

  cout << "End" << endl;
  return 1;
}
