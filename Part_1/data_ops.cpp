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

void input_parameters(std::string &data_s, std::string &func, std::string &hash){
  int choice{};

  if(data_s.empty()){
    cout << "Give the path to the dataset file: " << endl;
    cin >> data_s;
    cout << endl;
  }

  if(func.empty()){
    cout << "Specify the distance function: " << endl;
    cout << "1. DFT - Discrete Frechet Traversal." << endl;
    cout << "2. DTW - Dynamic Time Warping." << endl;
    //user gives a number and then we use the conditional operator
    cin >> choice;
    cout << endl;
    func = choice-1 ? "DTW" : "DFT";
  }

  if(hash.empty()){
    cout << "Specify the hash: " << endl;
    cout << "1. Classic." << endl;
    cout << "2. Probabilistic (LSH)." << endl;
    cin >> choice;
    cout << endl;
    hash = choice-1 ? "probabilistic" : "classic";
  }
}

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
    cout << "couldn't find data file!" << endl;
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
    cout << "couldn't find query file!" << endl;
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
