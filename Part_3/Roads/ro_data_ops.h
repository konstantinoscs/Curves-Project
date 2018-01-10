#ifndef DATA_OPS_H
#define DATA_OPS_H

#include <vector>
#include <string>

#include "../lib/curve.h"
#include "road.h"

//takes all the variables and assigns them from the command line arguments
bool parse_arguments(int argc, char ** argv, bool &parse, std::string &dist);

std::vector<way> read_ways(std::string way_s);

//takes a dataset file name and reads the curves from it
std::vector<std::vector<segment>> read_data_segs(std::string &data_s,
  const std::vector<way> &ways);

//print cluster results
void write_results(std::ofstream & out_f, double clustering_time,
  std::vector<std::vector<std::string>> & best_assignment,
  double Stotal, int i);

#endif
