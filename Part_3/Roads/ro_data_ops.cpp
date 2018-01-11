#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>

#include "../lib/curve.h"
#include "road.h"
#include "xml_ops.h"

using namespace std;

//data_ops contains all the functions for the intialization of the problem
//e.g. parsing command line arguments, getting input from the user,
//getting input from the files etc.

bool parse_arguments(int argc, char ** argv, bool& parse, string& dist){

  //we start from 1 to skip the name of the program
  int i{1};
  while(i<argc){
    if(!strcmp(argv[i],"-parse"))
      parse = true;
    else if(!strcmp(argv[i],"-dtw")){
      dist = "DTW2";
    }
    else
      cerr << "Wrong paramater given, it will be ignored" << endl;
    i++;
  }
  return true;
}

vector<way> read_ways(string way_s){
  vector<way> ways;
  way tway;
  ifstream data(way_s);
  size_t max = std::numeric_limits<streamsize>::max();
  while(data >> tway.id){
    tway.id.pop_back();
    data >> tway.type;
    tway.type.pop_back();
    ways.push_back(move(tway));
    data.ignore(max, '\n');
  }
  return ways;
}

//ind takes a type of way and returns its index in the vector
//where segments of this type of way are stored
inline size_t ind(string type){
  static string types[] {
    "motorway", "primary", "residential",
    "secondary", "service", "tertiary",
    "trunk", "unclassified"};
    for(size_t i=0; i<8; i++)
      if(!types[i].compare(type))
        return i;
}

size_t bin_search(const vector<way> &ways, string id){
  size_t l{0}, r{ways.size()-1}, i{(l+r)/2};
  node r_node;
  int comp = compare(ways[i].id, id);
  while(comp){
    if(comp > 0)
      r = --i;
    else
      l = ++i;
    i = (l+r)/2;
    comp = compare(ways[i].id, id);
  }
  return i;
}

//read_segment reads a segment from data file with "dimension" and puts it on
//oseg
bool read_segment(segment &oseg, ifstream &data, int dimension){
  //temp will be used to take all data
  string temp;
  int points_no{};
  //in coords we store all the coordinates of a single point
  vector<double> coords;
  //temp coordinate
  double t_coord;
  data >> temp;
  //check if we are in the end of the file
  if (data.eof())
    return false;

  oseg.set_dimension(dimension);
  temp.pop_back();
  oseg.set_id(temp);
  data >> temp;
  temp.pop_back();
  oseg.set_way(move(temp));
  data >> temp;
  points_no = stoi(temp);
  //main loop to read all the points
  for (int i = 0; i<points_no; i++){

    //loop to read the coordinates of all points
    for (int j=0; j<dimension; j++){
      data >> temp;
      t_coord = stod(temp);
      coords.push_back(t_coord);
    }
    oseg.set_point(std::move(coords));
    //we moved the vector so now we have to clear it
    coords.clear();
  }
  return true;
}

vector<vector<segment>> read_data_segs(string &data_s, const vector<way> &ways){
  string type;
  segment oseg{};
  ifstream data(data_s);
  vector<vector<segment>> segments(8);
  size_t i;

  //test if there is a file to get the data from
  if (!data.is_open()){
    cerr << "couldn't find data file!" << endl;
    exit(0);
  }

  while(true){
    if(!read_segment(oseg, data, 2))
      break;
    //cout << "a" << endl;
    i = bin_search(ways, oseg.get_way());
    type = ways[i].type;
    i = ind(type);
    segments[i].push_back(std::move(oseg));
  }
  return segments;
}

void write_results(ofstream & out_f, double clustering_time,
  vector<vector<string>> & best_assignment, double Stotal, int i){

  out_f << "    For road type " << i << ":" << endl;
  out_f << "k: " << best_assignment.size() << endl;
  out_f << "clustering_time: " << clustering_time << endl;
  out_f << "s: " << Stotal << endl;
  for(unsigned int i=0; i<best_assignment.size(); i++){
    out_f << "(Cluster " << i+1 << ":)";
    if(!best_assignment[i].size()) continue;
    for(unsigned int j=0; j<best_assignment[i].size()-1; j++)
      out_f << best_assignment[i][j] << "  ";
    out_f << best_assignment[i][best_assignment[i].size()-1] << endl;
  }
}


