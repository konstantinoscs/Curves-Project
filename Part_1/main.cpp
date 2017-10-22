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
  string data_s{"trajectories_dataset"}, query_s, out_s;
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
    return -1;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;

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
    concat_normalized_curves, v_size, normalized_curves);

  //concat_normalized_curves[0][0].print();
  int table_size = curves.size()/16;
  //L arrays of vectors of pointers(to real curves)
  //we need pointers to (1)real curves and (2)normalized curves
  vector<vector<vector<vector<real_curve*>>>> Lhashtable;
  hash_curves(concat_normalized_curves, dimension*k*v_size, Lhashtable,
    table_size, pcurves, normalized_curves);
  //L = concat_normalized_curves.size()

  //print_hashtable(Lhashtable[0],table_size);

/*  real_curve s0{curves[10]},s1{curves[432]};//only for testing
  s0.set_id("12345");
  s1.set_id("98765");*/
  vector<real_curve> s_curves{};
  double R{};
  //now you get the search curves
  read_query_curves(query_s, s_curves, dimension, R);

  /*s_curves.push_back(std::move(s0));
  s_curves.push_back(std::move(s1));
	int tsize{};
	tsize = s_curves.size();
  //next five lines must be in main..
  real_curve* nn_curve[tsize];//1
  double nn_distance[tsize];//2
  bool grid_curve_found[tsize];//3
	vector<string> curves_in_R[tsize];//4
  search_curves(s_curves, Lhashtable, k, 0, dimension, delta, table_size,
  	hash, func, pcurves, stats, R, nn_curve, nn_distance,
		grid_curve_found, curves_in_R);//5

	for(int i=0; i<s_curves.size(); i++){
		cout <<"id:"<<s_curves[i].get_id()<<endl;
		cout <<"nn_id:"<<nn_curve[i]->get_id()<<endl;
		cout <<"nn_dist:"<<nn_distance[i]<<endl;
		cout <<"grid_curve_found:"<<grid_curve_found[i]<<endl;
		cout <<"ids in R distance:" <<endl;
		for(int j=0; j<curves_in_R[i].size(); j++)
			cout <<curves_in_R[i][j]<<endl;
	}*/

  cout << "End" << endl;
  return 1;
}
