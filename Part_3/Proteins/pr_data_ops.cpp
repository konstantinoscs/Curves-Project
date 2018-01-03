#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <vector>

#include "../lib/curve.h"

using namespace std;

bool read_protein(real_curve & ocurve, int id, int N, int numC, ifstream & data){
  int points_no{};

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

bool parse_config(string config_s, int & numConform, int & N, vector<real_curve> & proteins){
  ifstream data(config_s);
  real_curve ocurve{};

  //We parse a file with the followin layout:
  /*numConform: <int>
  N: <int>
  X_1  Y_1  Z_1 
    .......        */

  data >> numConform;
  data >> N;

  for(int i=0;i<numConform;i++){
    read_protein(ocurve,i+1,N,numConform,data);
    proteins.push_back(std::move(ocurve));
  }

  data.close();

  return true;
}


