#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct node {
  string id;
  double lat;
  double lon;
  node();
  //move constructor
  node(node && mnode);
  //copy constructor in case move fails
  node(node & cnode);
};

node::node():id(""),lat(0), lon(0){}

node::node(node && mnode):id(std::move(mnode.id)), lat(mnode.lat),
  lon(mnode.lon){
  mnode.id.clear();
}

node::node(node & cnode):id(cnode.id), lat(cnode.lat), lon(cnode.lon){}

bool parse_xml(string data_s){
  ifstream data(data_s);
  vector<node> nodes;
  node t_node;
  string temp{};
  int counter{0};
  size_t max = std::numeric_limits<streamsize>::max();
  //ignore the first 3 lines of the xml file
  data.ignore(max, '\n');
  data.ignore(max, '\n');
  data.ignore(max, '\n');
  //start reading nodes;
  while(true){
    data >> temp;
    //cout << "Read " << temp << endl;
    //if it's not a node tag break
    if(!temp.compare("<node")){
      data >> temp;
      //copy the id
      t_node.id = std::move(temp.substr(4, temp.length()-5));
      //parse latitude
      data >> temp;
      t_node.lat = stod(temp.substr(5));
      //parse longitute
      data >> temp;
      t_node.lon = stod(temp.substr(5));
      //move node to the vector
      nodes.push_back(std::move(t_node));
      //cout << "Node read" << endl;
      counter++;
    }
    else if(!temp.compare("<way")){
      break;
    }
    //else{
    //}
    //ignore the rest of the line
    data.ignore(max, '\n');
  }

  while(true){
    if(!temp.compare("<way")){
      data.ignore(max, '\n');
    }
    else if(!temp.compare("<relation")){
      cout << "Will break" << endl;
      //relation tags are in the end of the file so we're done
      break;
    }
    data >> temp;
  }
  cout << "Nodes read: " << counter << endl;
  return true;
}
