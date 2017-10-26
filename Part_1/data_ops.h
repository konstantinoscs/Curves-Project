#ifndef DATA_OPS_H
#define DATA_OPS_H

#include <vector>
#include <string>

#include "curve.h"

bool parse_arguments(int argc, char ** argv, std::string &data_s,
std::string &query_s, int &k, int &L, std::string &out_s, bool &stats,
std::string &func, std::string &hash);

void input_parameters(std::string &data_s, std::string &func, std::string &hash);

bool read_dataset_curves(std::string data_s, std::vector<real_curve> & curves,
  int & dimension);

bool read_query_curves(std::string query_s, std::vector<real_curve> & curves,
  int dimension, double & R);

bool write_out_file(std::string out_s, std::string hash, std::string func,
  std::vector<real_curve> & s_curves, bool stats, int tsize, real_curve ** nn_curve,
  real_curve ** true_nn, double * nn_dist, double * nn_max_dist,
  double * nn_avg_dist, double * true_nn_dist, bool * grid_curve_found,
  std::vector<std::string> * curves_in_R, double * time1, double * time2);

#endif
