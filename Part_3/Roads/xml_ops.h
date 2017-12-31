#ifndef XML_OPS
#define XML_OPS
#include <string>
#include <vector>

#include "../lib/curve.h"
#include "road.h"

bool parse_xml(std::vector<road> & roads, std::vector<node> & nodes,
  const std::string & data_s, const std::string & out_s = "athens.csv");

std::vector<real_curve> make_segments(std::vector<road> &roads,
  std::vector<node> nodes);
#endif
