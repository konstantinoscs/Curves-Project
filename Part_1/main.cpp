#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "data_ops.h"
#include "curve.h"

using namespace std;


int main(int argc, char **argv){
  //k = locality sensitive functions
  //L  = number of hasthables
  int k{4}, L{5};
  bool stats{false};
  string data_s{}, query_s{}, out_s{};
  string func{}, hash{};
  //our curves aka the dataset
  vector<curve> curves;

  // cout << "k = "<< k << endl;
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash);

  // cout << data_s << endl << query_s << endl << out_s << endl;
  // cout << func << endl << hash << endl;
}
