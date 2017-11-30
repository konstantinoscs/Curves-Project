#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <utility>

#include "curve.h"

using namespace std;

//data_ops contains all the functions for the intialization of the problem
//e.g. parsing command line arguments, getting input from the user,
//getting input from the files etc.

bool parse_arguments(int argc, char ** argv, std::string &data_s,
std::string &query_s, int &k, int &L, std::string &out_s, bool &stats,
std::string &func, std::string &hash){

  //we start from 1 to skip the name of the program
  int i{1};
  while(i<argc){
    if(!strcmp(argv[i],"-d"))
      data_s = argv[++i];
    else if(!strcmp(argv[i],"-q"))
      query_s = argv[++i];
    else if(!strcmp(argv[i],"-k"))
      k = atoi(argv[++i]);
    else if(!strcmp(argv[i],"-L"))
      L = atoi(argv[++i]);
    else if(!strcmp(argv[i],"-o"))
      out_s = argv[++i];
    else if(!strcmp(argv[i],"-stats"))
      stats = true;
    else if(!strcmp(argv[i],"-function"))
      func = argv[++i];
    else if(!strcmp(argv[i],"-hash"))
      hash = argv[++i];
    else
      cerr << "Wrong paramater given, it will be ignored" << endl;
    //advance to the next parameter
    //if parameter required 2 arguments, one incremention is already done
      i++;
    }
  return true;
}

//read_curve reads a curve from data file with "dimension" and puts it on
//ocurve
bool read_curve(real_curve & ocurve, ifstream & data, int dimension){
  string id;
  int points_no{};
  //c is to get all the useless chars in the input e.g (),
  char c{};
  //in coords we store all the coordinates of a single point
  vector<double> coords;

  //temp coordinate
  double t_coord;

  data >> id;
  //check if we are in the end of the file
  if (data.eof()){
    cout << "Eof found!" << endl;
    return false;
  }
  ocurve.set_dimension(dimension);
  ocurve.set_id(id);
  data >> points_no;
  //main loop to read all the points
  for (int i = 0; i<points_no; i++){
    data >> c;              //get the first '('

    //loop to read the coordinates of all points
    for (int j = 0; j<dimension; j++){
      data >> t_coord;
      coords.push_back(t_coord);
      data >> c;      //get the comma after coordinate
    }

    ocurve.set_point(std::move(coords));
    //we moved the vector so now we have to clear it
    coords.clear();

    //get the comma between points - not applicable to last point
    if(i==points_no-1)
      break;
    data >> c;

  }
  return true;
}

bool read_dataset_curves(string data_s, vector<real_curve> & curves,
  int & dimension){

  string s;
  char c;
  real_curve ocurve{};
  ifstream data(data_s);

  //test if there is a file to get the data from
  if (!data.is_open()){
    cerr << "couldn't find data file!" << endl;
    return false;
  }

  //the first time id gets the "@dimension"
  data >> c;
  if (c=='@'){
    data >> s;
    cout << s <<endl;
    data >> dimension;
  }
  else{
    //if c!=@ then put it back because it's a curve_id
    data.putback(c);
    dimension = 2;
  }
  cout << "Dimension = " << dimension << endl;

  while(true){
    if(!read_curve(ocurve, data, dimension))
      break;
    //the speed up with move is amazing
    curves.push_back(std::move(ocurve));
  }

  data.close();
  return true;
}

bool read_query_curves(string query_s, vector<real_curve> & curves,
  int dimension, double & R){

  //s is used only to eat useless data
  string s;
  real_curve ocurve{};
  ifstream query(query_s);

  if (!query.is_open()){
    cerr << "couldn't find query file!" << endl;
    return false;
  }

  //get the "R:"
  query >> s ;
  query >> R;

  while(true){
    if(!read_curve(ocurve, query, dimension))
      break;
    //the speed up with move is amazing
    curves.push_back(std::move(ocurve));
  }

  query.close();
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


bool check_more(string & query_s){
  int choice{};
  bool more{};
  cout << "Would you like to give another query file?" << endl;
  cout << "1. Yes" << endl;
  cout << "2. No" << endl;
  cin >> choice;
  more = choice -1 ? false : true;
  if(more){
    cout << "Give path to the query file: " << endl;
    cin >> query_s;
  }
  return more;
}
