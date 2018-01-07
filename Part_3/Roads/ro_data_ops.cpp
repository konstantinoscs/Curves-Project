#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <utility>

#include "../lib/curve.h"

using namespace std;

//data_ops contains all the functions for the intialization of the problem
//e.g. parsing command line arguments, getting input from the user,
//getting input from the files etc.

bool parse_arguments(int argc, char ** argv, std::string &input_s,
std::string &config_s, std::string &out_s, std::string &func){

  //we start from 1 to skip the name of the program
  int i{1};
  while(i<argc){
    if(!strcmp(argv[i],"-i"))
    input_s = argv[++i];
    else if(!strcmp(argv[i],"-c"))
      config_s = argv[++i];
    else if(!strcmp(argv[i],"-o"))
      out_s = argv[++i];
    else if(!strcmp(argv[i],"-d"))
      func = argv[++i];
    else
      cerr << "Wrong paramater given, it will be ignored" << endl;
    //advance to the next parameter
    //if parameter required 2 arguments, one incremention is already done
      i++;
    }
  return true;
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
  if (data.eof()){
    cout << "Eof found!" << endl;
    return false;
  }
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

bool read_data_segs(string &data_s, vector<segment> & segments){
  string s;
  segment oseg{};
  ifstream data(data_s);

  //test if there is a file to get the data from
  if (!data.is_open()){
    cerr << "couldn't find data file!" << endl;
    return false;
  }

  while(true){
    if(!read_segment(oseg, data, 2))
      break;
    //the speed up with move is amazing
    segments.push_back(std::move(oseg));
  }

  data.close();
  return true;
}

bool write_results(ofstream & out_f, vector<real_curve*> & centroids,
  vector<vector<real_curve*>> assignment, vector<double> Si, double Stotal,
  int i, int j, int z, string dist, bool complete, double time, int dimension){

  if (!out_f.is_open()){
    cerr << "couldn't create output  file!" << endl;
    return false;
  }
  out_f << "Algorithm: ";
  if(i) out_f << "[Kmeans_Init]";
  else out_f << "[Random_Init]";
  if(j) out_f << "+[Range_Assign]";
  else out_f << "+[Simple_Assign]";
  if(z) out_f << "+[PAM]" << endl;
  else out_f << "+[Mean_Frechet]" << endl;
  out_f << "Metric: ";
  if(dist=="DFT") out_f << "Frechet" << endl;
  else out_f << "DTW" << endl;
  if(!complete){
    for(unsigned int t=0; t<centroids.size(); t++){
      out_f << "Cluster-" << t+1;
      out_f << " {size: " << assignment[t].size() << ", centroid: ";
      if(centroids[t]->get_id().compare("-1"))//id != -1
        out_f << centroids[t]->get_id();
      else{
        out_f << "[";
        for(unsigned int y=0; y<centroids[t]->get_points().size(); y++){
          out_f << "(";
          for(int x=0; x<dimension-1; x++)
            out_f << centroids[t]->get_points()[y][x] << ",";
          out_f << centroids[t]->get_points()[y][dimension-1] << ")";
          if(y != centroids[t]->get_points().size()-1) out_f << ",";
        }
        out_f << "]";
      }
      out_f << "}" << endl;
    }
    out_f << "Clustering Time: " << time << endl;
    out_f << "Silhouette: [";
    for(unsigned int t=0; t<centroids.size(); t++)
      out_f << Si[t] << ",";
    out_f << Stotal << "]" << endl;
  }
  else{
    for(unsigned int t=0; t<centroids.size(); t++){
      out_f << "Cluster-" << t+1 << "{";
      for(unsigned int y=0; y<assignment[t].size()-1; y++)
        out_f << assignment[t][y]->get_id() << ",";
      out_f << assignment[t][assignment[t].size()-1]->get_id() << "}" << endl;
    }
  }
  out_f << endl;
  //delete remaining mean curves
  for(unsigned int t=0; t<centroids.size(); t++)
    if(!centroids[t]->get_id().compare("-1"))
      delete centroids[t];
  return true;
}
