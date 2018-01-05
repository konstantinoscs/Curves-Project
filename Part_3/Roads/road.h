#ifndef ROAD_H
#define ROAD_H
#include <string>
#include <vector>

struct node {
  std::string id;
  double lat;
  double lon;
  int refs;
  node();
  void print();
};

struct road{
  std::string id;
  std::string type;
  std::vector<int> nodes;
};


#endif
