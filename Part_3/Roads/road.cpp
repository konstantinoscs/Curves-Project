#include <iostream>
#include "road.h"

node::node():id(""), lat(0), lon(0), refs(0){}

void road::print(){
  std::cout << id<< '\n';
  for(int i=0; i<nodes.size(); i++){
    std::cout << nodes[i] << '\n';
  }
}
