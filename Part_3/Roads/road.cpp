#include <iostream>
#include <utility>

#include "road.h"

using namespace std;

node::node():id(""),lat(0), lon(0){}

node::node(node && mnode):id(move(mnode.id)), lat(mnode.lat),
  lon(mnode.lon){
  mnode.id.clear();
}

node::node(const node & cnode):id(cnode.id), lat(cnode.lat), lon(cnode.lon){}

void node::print(){
  cout << "Node " << id << " lat:" << lat << " lon:" << lon << '\n';
}

road::road(road && m_road):id(move(m_road.id)), type(move(m_road.type)),
  nodes(move(m_road.nodes)){
  m_road.id.clear();
  m_road.type.clear();
  m_road.nodes.clear();
  }
