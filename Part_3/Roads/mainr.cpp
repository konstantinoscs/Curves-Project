#include <iostream>
#include <string>
#include <ctime>

#include "../lib/curve.h"
#include "ro_data_ops.h"
#include "road.h"
#include "xml_ops.h"

using namespace std;

int main(int argc, char **argv){
  bool parse{false};
  vector<way> ways;
  vector<vector<segment>> segments;
  string data_s{"segments.csv"}, way_s{"athens.csv"};
  parse_arguments(argc, argv, parse);
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
  ways = read_ways(way_s);
  segments = read_data_segs(data_s, ways);
  t=clock() -t;
  cout << "Parsing segments time: " << float(t)/CLOCKS_PER_SEC << '\n';
  cout << ways[ways.size()-1].id << ' ' << ways[ways.size()-1].type << endl;
  for(size_t i=0; i<segments.size(); i++)
    cout << segments[i].size() << endl;
}
