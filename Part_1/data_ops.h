#ifndef DATA_OPS_H
#define DATA_OPS_H
#include <vector>
#include "curve.h"

int parse_arguments(int argc, char ** argv, std::string &data_s,
  std::string &query_s, int &k, int &L, std::string &out_s, bool &stats,
  std::string &func, std::string &hash);

void input_parameters(std::string &data_s, std::string &func, std::string &hash);

int read_dataset_curves(std::string const data_s, std::vector<curve> & curves,
  int & dimension);

#endif
