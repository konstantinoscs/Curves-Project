#include <iostream>
#include <fstream>
#include <string>

#include "data_ops.h"

using namespace std;


int main(int argc, char **argv){
  //k = locality sensitive functions
  //L  = number of hasthables
  int k{4}, L{5};
  bool stats{false};
  string data_s{}, query_s{}, out_s{};
  string func{}, hash{};

  // cout << "k = "<< k << endl;
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash);

  ifstream data("data_s");
  ifstream query("query_s");

  // cout << data_s << endl << query_s << endl << out_s << endl;
  // cout << func << endl << hash << endl;

  //test if there is a file to get the data from
  if (!data.is_open())
    cout << "couldn't find data file!" << endl;

  data.close();
  query.close();
  ofstream output("out_s");

  output.close();
}
