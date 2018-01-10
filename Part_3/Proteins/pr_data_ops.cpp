#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <vector>

#include "../lib/curve.h"

using namespace std;

bool parse_arguments(int argc, char **argv, string & input){
  //we start from 1 to skip the name of the program
  int i{1};
  bool flag{false};
  while(i<argc){
    if(!strcmp(argv[i],"-i")){
      input = argv[++i];
      flag = true;
    }
    else
      cerr << "Wrong paramater given, it will be ignored" << endl;
    //advance to the next parameter
    //if parameter required 2 arguments, one incremention is already done
    i++;
  }
  //if not given input file return false and stop the program
  return flag;
}

bool read_protein(real_curve & ocurve, int id, int N, int numC, ifstream & data){

  //in coords we store all the coordinates of a single point
  vector<double> coords;

  //temp coordinate
  double t_coord;

  //check if we are in the end of the file
  if (data.eof() && id==numC){
    cout << "Eof found!" << endl;
    return false;
  }

  ocurve.set_dimension(3);
  ocurve.set_id(to_string(id));
  //main loop to read all the points
  for (int i = 0; i<N; i++){
    data >> t_coord; //X
    coords.push_back(t_coord);
    data >> t_coord; //Y
    coords.push_back(t_coord);
    data >> t_coord; //Z
    coords.push_back(t_coord);

    ocurve.set_point(std::move(coords));
    //we moved the vector so now we have to clear it
    coords.clear();
  }
  return true;
}

bool parse_input(string config_s, int & numConform, int & N, vector<real_curve> & proteins){
  ifstream data(config_s);
  real_curve ocurve{};

  //We parse a file with the followin layout:
  /*numConform: <int>
  N: <int>
  X_1  Y_1  Z_1 
    .......        */

  data >> numConform;
  if(!numConform) return false;//empty input
  data >> N;

  for(int i=0;i<numConform;i++){
    read_protein(ocurve,i+1,N,numConform,data);
    proteins.push_back(std::move(ocurve));
  }

  data.close();

  return true;
}

void write_results(string out_s,
  vector<vector<string>> & best_assignment,double Stotal){

  ofstream out_f;
  out_f.open(out_s, ofstream::out | ofstream::trunc);
  out_f << "k: " << best_assignment.size() << endl;
  out_f << "s: " << Stotal << endl;
  for(unsigned int i=0; i<best_assignment.size(); i++){
    out_f << "(Cluster " << i+1 << ":)";
    for(unsigned int j=0; j<best_assignment[i].size()-1; j++)
      out_f << best_assignment[i][j] << "  ";
    out_f << best_assignment[i][best_assignment[i].size()-1] << endl;
  }
  out_f.close();
}

