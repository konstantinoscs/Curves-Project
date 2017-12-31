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
  //move constructor
  node(node && mnode);
  //copy constructor in case move fails
  node(const node & cnode);
  void print();
};

struct road{
  std::string id;
  std::string type;
  std::vector<std::string> nodes;
  road() = default;
  road(road && m_road);
};


#endif
