#include <iostream>
#include <string>
#include <ctime>

#include "../lib/curve.h"
#include "ro_data_ops.h"
#include "road.h"
#include "xml_ops.h"

using namespace std;

int main(int argc, char **argv){
  bool parse{true};
  vector<segment> segments;
  string data_s{"segments.csv"};
  if(parse){
    string xml_s{"athens_greece.osm"};
    vector<road> roads;
    vector<node> nodes;
    clock_t t = clock();
    parse_xml(roads, nodes, xml_s);
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
  read_data_segs(data_s, segments);
  segments[0].print();
}
