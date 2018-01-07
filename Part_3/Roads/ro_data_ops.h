#ifndef DATA_OPS_H
#define DATA_OPS_H

#include <vector>
#include <string>

#include "../lib/curve.h"

//takes all the variables and assigns them from the command line arguments
bool parse_arguments(int argc, char ** argv, std::string &input_s,
std::string &config_s, std::string &out_s, std::string &func);

//takes a dataset file name and reads the curves from it
bool read_data_segs(std::string &data_s, std::vector<segment> &segments);

//print cluster results
bool write_results(std::ofstream & out_f, std::vector<real_curve*> & centroids,
  std::vector<std::vector<real_curve*>> assignment, std::vector<double> Si,
  double Stotal, int i, int j, int z, std::string dist, bool complete,
  double time, int dimension);

#endif
