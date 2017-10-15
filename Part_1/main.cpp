#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

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

  vector<vector<norm_curve>> concat_normalized_curves{};
  Lconcatenate_kcurves(k,L,curves,dimension,delta,concat_normalized_curves);

  //concat_normalized_curves[0][0].print();

  cout << "End" << endl;
  return 1;
}
