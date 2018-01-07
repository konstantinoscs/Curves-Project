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

size_t binary_search(vector<node> & nodes, string id){
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
      nodes.push_back(move(t_node));
      //cout << "Node read" << endl;
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
      nds.push_back(move(temp.substr(5, temp.length()-8)));
    }
    else if(!temp.compare("<tag")){
      data >> temp;
      if(!temp.compare("k=\"highway\"")){
        data >> temp;
        type = temp.substr(3, temp.length()-6);
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

//index takes a type of way and returns its index in the vector
//where segments of this type of way are stored
inline size_t index(string type){
  static string types[] {
    "motorway", "primary", "residential",
    "secondary", "service", "tertiary",
    "trunk", "unclassified"};
    for(size_t i=0; i<7; i++)
      if(!types[i].compare(type))
        return i;
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
  coords.clear();
}

void make_segments(const vector<road> &roads, const vector<node> &nodes,
  const string &out_s){
  ofstream out(out_s);
  bool write{false};
  double l1{}, l2{}, l3{}, curb{}, thrs{0.03}, curv{};
  int segid{}, count{}, tot_n{};
  int maxsize{}, minsize{std::numeric_limits<int>::max()};
  size_t nthrs{200}, minthrs{5};
  vector<double> coords;
  cout << "Curvatures:\n";
  for(size_t i=0; i<roads.size(); i++){
    coords.push_back(nodes[roads[i].nodes[0]].lat);
    coords.push_back(nodes[roads[i].nodes[0]].lon);
    if(roads[i].nodes.size() ==1){
      //special case
      out << segid << ", " << roads[i].id << ", " << 1 << ", ";
      out << coords[0] << ", " << coords[1] << '\n';
      segid++;
      coords.clear();
      continue;
    }
    if(roads[i].nodes.size()<minthrs){
      for(size_t j=0; j<roads[i].nodes.size(); j++){
        coords.push_back(nodes[roads[i].nodes[j]].lat);
        coords.push_back(nodes[roads[i].nodes[j]].lon);
      }
      write_segment(out, segid, roads[i].id, coords, minsize, maxsize, tot_n);
      continue;
    }
    for(size_t j=1; j<roads[i].nodes.size()-minthrs; j++){
      l1 = euclid_dist(nodes[roads[i].nodes[j-1]].lat, nodes[roads[i].nodes[j-1]].lon,
        nodes[roads[i].nodes[j]].lat, nodes[roads[i].nodes[j]].lon);
      l2 = euclid_dist(nodes[roads[i].nodes[j]].lat, nodes[roads[i].nodes[j]].lon,
        nodes[roads[i].nodes[j+1]].lat, nodes[roads[i].nodes[j+1]].lon);
      l3 = euclid_dist(nodes[roads[i].nodes[j+1]].lat, nodes[roads[i].nodes[j+1]].lon,
        nodes[roads[i].nodes[j-1]].lat, nodes[roads[i].nodes[j-1]].lon);

      curb = curvature(l1,l2,l3);
      count++;
      if(isfinite(curb) && curb <=1)
        curv += curb;
      //cout << curb << endl;
      if(coords.size()/2+1 <= minthrs){
        coords.push_back(nodes[roads[i].nodes[j]].lat);
        coords.push_back(nodes[roads[i].nodes[j]].lon);
      }
      else if(nodes[roads[i].nodes[j]].refs >=2 && nodes[roads[i].nodes[j+1]].refs ==1){
        coords.push_back(nodes[roads[i].nodes[j]].lat);
        coords.push_back(nodes[roads[i].nodes[j]].lon);
        //indicate that we have to flush next
        write = true;
      }
      else if (curb>thrs || coords.size()/2+1 >= nthrs || write){
        //check for curvature or maxsize
        coords.push_back(nodes[roads[i].nodes[j]].lat);
        coords.push_back(nodes[roads[i].nodes[j]].lon);
        write_segment(out, segid, roads[i].id, coords, minsize, maxsize, tot_n);
        write = false;
      }
      else{
        coords.push_back(nodes[roads[i].nodes[j]].lat);
        coords.push_back(nodes[roads[i].nodes[j]].lon);
      }
    }

    for(size_t j=roads[i].nodes.size()-minthrs; j<roads[i].nodes.size(); j++){
      coords.push_back(nodes[roads[i].nodes[j]].lat);
      coords.push_back(nodes[roads[i].nodes[j]].lon);
    }
    write_segment(out, segid, roads[i].id, coords, minsize, maxsize, tot_n);
  }
  cout << "Maxsize: " << maxsize << '\n';
  cout << "Minsize: " << minsize << '\n';
  cout << "Segs: " << segid << '\n';
  cout << "Nodes written: " << tot_n << '\n';
  cout << "Average curvature: " << double(curv/count) << endl;
}
