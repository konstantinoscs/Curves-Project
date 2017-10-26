#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <limits>

#include "data_ops.h"
#include "search_ops.h"
#include "curve.h"
#include "curve_ops.h"
#include "hash_f.h"
#include "general_hash.h"
#include "lsh.h"
#include "entry.h"

#define REPETITIONS 100

using namespace std;

int main(int argc, char **argv){
  //k = locality sensitive functions
  //L  = number of hashtables
  //w = window for the hs
  int k{4}, L{5}, w{4}, kvec{4};
  double delta{};
  clock_t begin, end;
  int dimension{}, v_size{};
  bool stats{false}, more{true};
  int rep_constant{};
  int table_size{};
  string data_s{}, query_s{}, out_s{"results"};
  string func, hash;
  //our curves aka the dataset
  vector<real_curve> curves{};
	vector<real_curve*> pcurves{};
  vector<hash_f> hs;
  cout << std::fixed;
  cout << std::setprecision(17);
  srand(time(0));

  //initialize all parameters
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash, query_s);

  //data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
    return -1;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;

  for(size_t i=0; i<curves.size(); i++)
		pcurves.push_back(&curves[i]);

  //delta = R>0.002 ? 4*dimension*R : 0.01;
  delta = 0.05;
	rep_constant = stats ? REPETITIONS : 1;
	table_size = curves.size()/32;

  do{
  vector<real_curve> s_curves{};
   double R{};
 	//here should be a do...while loop
 	//now gets the search curves
 	if(!read_query_curves(query_s, s_curves, dimension, R)){
    cerr << "Something went wrong while reading the search queries!"<< endl;
    return -1;
  }

 	int tsize{};
	tsize = s_curves.size();

  cout << "Read " << s_curves.size() << " search curves" << endl;
  //used only if stats==false(1,2,3)
	real_curve* nn_curve[tsize];//1.nearest neighbor for every s curve
 	bool grid_curve_found[tsize];//2
	vector<string> curves_in_R[tsize];//3.ids from all curves in R distance
  double nn_dist[tsize];//4.if stats==true used as min distance
	double nn_max_dist[tsize];
	double nn_avg_dist[tsize];
  double elapsed_time_1[tsize], elapsed_time_2[tsize];
	double double_max{std::numeric_limits<double>::max()};
	//init min/max dist and elapsed_time_1
	for(int i=0; i<tsize; i++){
		nn_dist[i] = double_max;
		nn_max_dist[i] = 0.0;
		elapsed_time_1[i] = 0.0;
	}

	for(int i=0; i<rep_constant; i++){
		vector<real_curve> normalized_curves{};
	  vector<vector<norm_curve>> concat_normalized_curves{};
  	//L arrays of vectors of entries we need pointers to:
  	//(1)real curves and (2)normalized curves(== entry)
  	vector<vector<vector<entry>>> Lhashtable{};

  	Lconcatenate_kcurves(k, L ,curves, dimension, delta,
  	  concat_normalized_curves, v_size, normalized_curves);

  	hash_curves(concat_normalized_curves, dimension*k*v_size, Lhashtable,
  	  table_size, pcurves, normalized_curves, hash, kvec, w);

		double temp_nn_dist[tsize];

  	search_curves(s_curves, Lhashtable, k, 0, dimension, delta, table_size,
  		hash, func, pcurves, stats, R, nn_curve, temp_nn_dist,
			grid_curve_found, curves_in_R, w, elapsed_time_1);

		for(int i=0; i<tsize; i++){
			begin = clock();
			nn_dist[i] = min(nn_dist[i],temp_nn_dist[i]);
			nn_max_dist[i] = max(nn_max_dist[i],temp_nn_dist[i]);
			nn_avg_dist[i] += temp_nn_dist[i]/REPETITIONS;
			end = clock();
			elapsed_time_1[i] += double(end - begin) / CLOCKS_PER_SEC;
		}
	}
	double true_nn_dist[tsize];
	real_curve* true_nn[tsize];
	vector<string> temp;
	for(int i=0; i<tsize; i++){//find true nn for all s_curves
		begin = clock();
		find_nn(s_curves[i], pcurves, dimension, func, true_nn[i],
			true_nn_dist[i], true, 0, temp);
		end = clock();
		elapsed_time_2[i] = double(end - begin) / CLOCKS_PER_SEC;
	}
  write_out_file(out_s, hash, func, s_curves, stats, tsize, nn_curve, true_nn,
    nn_dist, nn_max_dist, nn_avg_dist, true_nn_dist, grid_curve_found,
    curves_in_R, elapsed_time_1, elapsed_time_2);
  more = check_more(query_s);
}while(more);
  cout << "End" << endl;
  return 1;
}
