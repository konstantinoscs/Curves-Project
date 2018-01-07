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
  clock_t t = clock();
  if(parse){
    string xml_s{"athens_greece.osm"};
    vector<road> roads;
    vector<node> nodes;
    parse_xml(roads, nodes, xml_s);
    t = clock() -t;
    cout << "Parsing time: " << float(t)/CLOCKS_PER_SEC << '\n';
    //cout << roads.size() << '\n';
    //cout << nodes.size() << endl;
    t = clock();
    make_segments(roads, nodes);
    t = clock() -t;
    cout << "Segmenting time: " << float(t)/CLOCKS_PER_SEC << '\n';
    roads.clear();
    nodes.clear();
  }
  t=clock();
  read_data_segs(data_s, segments);
  t=clock() -t;
  cout << "Parsing segments time: " << float(t)/CLOCKS_PER_SEC << '\n';
}
