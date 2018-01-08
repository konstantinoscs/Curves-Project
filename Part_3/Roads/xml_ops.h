#ifndef XML_OPS
#define XML_OPS
#include <string>
#include <vector>

#include "road.h"

bool parse_xml(std::vector<road> & roads, std::vector<node> & nodes,
  const std::string & data_s, const std::string & out_s = "athens.csv");

int compare(const std::string &s1, const std::string &s2);

void make_segments(const std::vector<road> &roads, const std::vector<node> &nodes,
  const std::string &out_s = "segments.csv");
#endif
