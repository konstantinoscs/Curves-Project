#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "../lib/curve.h"
//#include "../lib/distance_ops.h"
#include "road.h"

using namespace std;

inline void check_highway(string & type){
  if(!type.compare("motorway") || !type.compare("primary")){
    return ;
  }
  else if(!type.compare("residential") || !type.compare("secondary")){
    return ;
  }
  else if(!type.compare("service") || !type.compare("tertiary")){
    return ;
  }
  else if(!type.compare("trunk") || !type.compare("unclassified")){
    return ;
  }
  type.clear();
}

inline int compare(const string & s1, const string & s2){
  size_t l1{s1.length()}, l2{s2.length()};
  if(l1 > l2)
    return 1;
  else if (l2 > l1)
    return -1;
  else
    return s1.compare(s2);
}

size_t binary_search(vector<node> &nodes, string id){
  size_t l{0}, r{nodes.size()-1}, i{(l+r)/2};
  node r_node;
  int comp = compare(nodes[i].id, id);
  while(comp){
    if(comp > 0)
      r = --i;
    else
      l = ++i;
    i = (l+r)/2;
    comp = compare(nodes[i].id, id);
  }
  return i;
}

//write nodes writes the athens.csv file with the roads info
//and returns a vector of the indexes of a way's nodes in the
//general nodes vector
inline vector<int> write_nodes(ofstream & out, vector<node> & nodes, vector<string> & nds){
  size_t target{0};
  vector<int> node_i;
  for(size_t i=0; i<nds.size(); i++){
    target = binary_search(nodes, nds[i]);
    out << ", " << nodes[target].lat << ", " << nodes[target].lon;
    //mark that we've encountered this node before in a road
    nodes[target].refs++;
    node_i.push_back(target);
  }
  return node_i;
}

bool parse_xml(vector<road> & roads, vector<node> & nodes, const string &data_s,
  const string &out_s){
  ifstream data(data_s);
  ofstream out(out_s);
  vector<string> nds;
  node t_node;
  road t_road;
  string temp{}, type{}, id{};
  int counter{0};
  size_t max = std::numeric_limits<streamsize>::max();
  if(!data.is_open()){
    cerr << "File for parsing not found!\n";
    return false;
  }
  nodes.reserve(3004103);
  roads.reserve(89701);
  //ignore the first 3 lines of the xml file
  data.ignore(max, '\n');
  data.ignore(max, '\n');
  data.ignore(max, '\n');
  //start reading nodes;
  while(true){
    data >> temp;
    //if it's not a node tag break
    if(!temp.compare("<node")){
      data >> temp;
      //copy the id
      t_node.id.assign(temp, 4, temp.length()-5);
      //parse latitude
      data >> temp;
      t_node.lat = stod(temp.substr(5));
      //parse longitute
      data >> temp;
      t_node.lon = stod(temp.substr(5));
      //move node to the vector
      nodes.push_back(std::move(t_node));
      //std::cout << "Node read" << endl;
      t_node.id.clear();
      counter++;
    }
    else if(!temp.compare("<way")){
      break;
    }
    //ignore the rest of the line
    data.ignore(max, '\n');
  }

  //start reading roads
  while(true){
    if(!temp.compare("<way")){
      data >> temp;
      id.assign(temp, 4, temp.length()-5);
      //id = temp.substr(4, temp.length()-5);
    }
    else if(!temp.compare("<nd")){
      data >> temp;
      nds.push_back(std::move(temp.substr(5, temp.length()-8)));
    }
    else if(!temp.compare("<tag")){
      data >> temp;
      if(!temp.compare("k=\"highway\"")){
        data >> temp;
        type = std::move(temp.substr(3, temp.length()-6));
        //check if it's a highway we're interested in
        check_highway(type);
      }
    }
    else if(!temp.compare("</way>")){
      //write road to file if valid
      if(!type.empty()){
        out << id << ", " << type;
        t_road.nodes = write_nodes(out, nodes, nds);
        out << endl;
        t_road.id = move(id);
        t_road.type = move(type);
        roads.push_back(move(t_road));
      }
      id.clear();
      type.clear();
      nds.clear();
    }
    else if(!temp.compare("<relation")){
      //relation tags are in the end of the file so we're done
      break;
    }
    data.ignore(max, '\n');
    data >> temp;
  }
  return true;
}

inline double euclid_dist(double x1, double y1, double x2, double y2){
	double temp{}, ed{};
	temp = x1 - x2;
	ed += temp * temp;
	temp = y1 - y2;
	ed += temp * temp;
	return sqrt(ed);
}

inline double curvature(double l1, double l2, double l3){
  return l1*l2*l3/sqrt((l1+l2+l3)*(l2+l3-l1)*(l3+l1-l2)*(l1+l2-l3));
}

void write_segment(ofstream &out, int &id, string way_id, vector<double> &coords,
  int &minsize, int &maxsize, int &tot_n){
  out << id << ", " << way_id << ", " << coords.size()/2 << ", ";
  for(size_t i=0; i<coords.size()-1; i++){
    out << coords[i] << ", ";
  }
  out << coords.back() << '\n';
  //check if we have new max/min
  if(coords.size()/2 < minsize)
    minsize = coords.size()/2;
  else if(coords.size()/2 > maxsize)
    maxsize = coords.size()/2;
  //ingrement the id
  id++;
  tot_n += coords.size()/2;
  //keep last node because it's also a part of the next segment
  coords.erase(coords.begin(), coords.end()-2);
}

void make_segments(const vector<road> &roads, const vector<node> &nodes,
  const string &out_s){
  ofstream out(out_s);
  bool write{false};
  //lengths for every 3 points, total and temporary curvatures
  double l1{}, l2{}, l3{}, curb{}, curv{};
  double thrs{0.03};  //curvature threshold over which a segment breaks
  int segid{};  //serial segment id for every new segment
  //count for average curvature, tot_n -> nodes written
  int count{}, tot_n{}, totalnodes{};
  //min and max segment sizes for the statistics
  int maxsize{}, minsize{std::numeric_limits<int>::max()};
  size_t nthrs{200}, minthrs{4}; //min and max threshold for segment size
  vector<double> coords; //keep all the coordinates until written to file

  std::cout << "Segmenting:\n";
  for(size_t i=0; i<roads.size(); i++){
    totalnodes += roads[i].nodes.size();
    coords.push_back(nodes[roads[i].nodes[0]].lat);
    coords.push_back(nodes[roads[i].nodes[0]].lon);
    //special case for roads with one node
    if(roads[i].nodes.size() ==1){
      out << segid << ", " << roads[i].id << ", " << 1 << ", ";
      out << coords[0] << ", " << coords[1] << '\n';
      segid++;
      tot_n++;
      coords.clear();
      continue;
    }
    //make one segment for small roads (according to minthrs)
    if(roads[i].nodes.size() <= minthrs){
      for(size_t j=1; j<roads[i].nodes.size(); j++){
        coords.push_back(nodes[roads[i].nodes[j]].lat);
        coords.push_back(nodes[roads[i].nodes[j]].lon);
      }
      write_segment(out, segid, roads[i].id, coords, minsize, maxsize, tot_n);
      continue;
    }
    //for every other road segment it according to heuristics
    for(size_t j=1; j<roads[i].nodes.size()-minthrs; j++){
      //find the 3 sides of the triangle for every 3 points
      l1 = euclid_dist(nodes[roads[i].nodes[j-1]].lat, nodes[roads[i].nodes[j-1]].lon,
        nodes[roads[i].nodes[j]].lat, nodes[roads[i].nodes[j]].lon);
      l2 = euclid_dist(nodes[roads[i].nodes[j]].lat, nodes[roads[i].nodes[j]].lon,
        nodes[roads[i].nodes[j+1]].lat, nodes[roads[i].nodes[j+1]].lon);
      l3 = euclid_dist(nodes[roads[i].nodes[j+1]].lat, nodes[roads[i].nodes[j+1]].lon,
        nodes[roads[i].nodes[j-1]].lat, nodes[roads[i].nodes[j-1]].lon);
      //compute circumcircle radius (curvature)
      curb = curvature(l1,l2,l3);
      count++;
      //exclude the roads with curvature >1 from average curvature
      if(isfinite(curb) && curb <=1)
        curv += curb;

      coords.push_back(nodes[roads[i].nodes[j]].lat);
      coords.push_back(nodes[roads[i].nodes[j]].lon);
      //start checking if we need to "cut" the segment
      //if the segment is too small don't cut it no matter what
      if(coords.size()/2+1 <= minthrs){
        continue;
      }
      else if(nodes[roads[i].nodes[j]].refs >=2 && nodes[roads[i].nodes[j+1]].refs ==1){
        //indicate that we have to flush next
        write = true;
      }
      else if(curb>thrs || coords.size()/2+1 >= nthrs || write){
        //check for curvature or maxsize
        write_segment(out, segid, roads[i].id, coords, minsize, maxsize, tot_n);
        write = false;
      }
    }

    for(size_t j=roads[i].nodes.size()-minthrs; j<roads[i].nodes.size(); j++){
      coords.push_back(nodes[roads[i].nodes[j]].lat);
      coords.push_back(nodes[roads[i].nodes[j]].lon);
    }
    write_segment(out, segid, roads[i].id, coords, minsize, maxsize, tot_n);
    coords.clear();
  }
  std::cout << "Maxsize: " << maxsize << '\n';
  std::cout << "Minsize: " << minsize << '\n';
  std::cout << "Segs: " << segid << '\n';
  std::cout << "Nodes written: " << tot_n << '\n';
  std::cout << "Total nodes were: " << totalnodes << '\n';
  std::cout << "Average curvature: " << double(curv/count) << endl;
}
