#ifndef DATA_OPS_H
#define DATA_OPS_H

#include <vector>
#include <string>

#include "curve.h"

//takes all the variables and assigns them from the command line arguments
bool parse_arguments(int argc, char ** argv, std::string &data_s,
std::string &query_s, int &k, int &L, std::string &out_s, bool &stats,
std::string &func, std::string &hash);

//gets input from user and assigns the variables
void input_parameters(std::string &data_s, std::string &func, std::string &hash,
  std::string & query_s);

//takes a dataset file name and reads the curves from it
bool read_dataset_curves(std::string data_s, std::vector<real_curve> & curves,
  int & dimension);

//takes query file name and reads the curves from it
bool read_query_curves(std::string query_s, std::vector<real_curve> & curves,
  int dimension, double & R);

//print cluster results
bool write_results(std::ofstream & out_f, std::vector<real_curve*> & centroids,
  std::vector<std::vector<real_curve*>> assignment, std::vector<double> Si,
  double Stotal, int i, int j, int z, std::string dist, bool complete,
  double time);

//prints the results file
bool write_out_file(std::string out_s, std::string hash, std::string func,
  std::vector<real_curve> & s_curves, bool stats, int tsize, real_curve ** nn_curve,
  real_curve ** true_nn, double * nn_dist, double * nn_max_dist,
  double * nn_avg_dist, double * true_nn_dist, bool * grid_curve_found,
  std::vector<std::string> * curves_in_R, double * time1, double * time2);

//checks if the user wants to test more queries
bool check_more(std::string & query_s);

#endif
