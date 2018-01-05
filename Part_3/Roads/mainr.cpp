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
    clock_t te = clock();
    cout << "Parsing time: " <<float(te-t)/CLOCKS_PER_SEC << '\n';
    //cout << roads.size() << '\n';
    //cout << nodes.size() << endl;
    make_segments(roads, nodes);
    te = clock() -te;
    cout << "Segmenting time: " <<float(te)/CLOCKS_PER_SEC << '\n';
    roads.clear();
    nodes.clear();
  }
}
