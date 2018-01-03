#ifndef PR_DATA_OPS_H
#define PR_DATA_OPS_H

#include <string>
#include <vector>

#include "../lib/curve.h"

bool parse_config(std::string config_s, int & numConform, int & N, std::vector<real_curve> & proteins);

#endif
