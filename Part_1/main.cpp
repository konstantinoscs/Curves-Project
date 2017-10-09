#include <iostream>
#include <fstream>
#include <string>

#include "data_ops.h"

using namespace std;

int main(int argc, char **argv){
  //k = locality sensitive functions
  //L  = number of hasthables
  int k = 4, L = 5;
  bool stats = false;
  string data_s{}, query_s{}, out_s{};
  string func{}, hash{};

  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  ifstream data("data_s");
  ifstream query("query_s");

  data.close();
  query.close();
  ofstream output("out_s");

  output.close();
}
