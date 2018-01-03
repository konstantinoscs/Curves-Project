#include <iostream>
#include <string>
#include <ctime>

#include "road.h"
#include "xml_ops.h"

using namespace std;

int main(int argc, char **argv){
  bool parse{true};
  if(parse){
    string data_s{"athens_greece.osm"};
    vector<road> roads;
    vector<node> nodes;
    clock_t t = clock();
    parse_xml(roads, nodes, data_s);
    t = clock() -t;
    cout << "Time: " <<float(t)/CLOCKS_PER_SEC << endl;
    cout << roads.size() << endl;
    cout << nodes.size() << endl;
  }
}
