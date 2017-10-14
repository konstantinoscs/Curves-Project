#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

#include "data_ops.h"
#include "curve.h"
#include "curve_ops.h"

using namespace std;


int main(int argc, char **argv){
  //k = locality sensitive functions
  //L  = number of hasthables
  int k{4}, L{5};
  double delta{};
  int dimension{};
  bool stats{false};
  string data_s, query_s, out_s;
  string func, hash;
  //our curves aka the dataset
  vector<curve> curves;
  vector<double> t;
  std::cout << std::fixed;
  cout << std::setprecision(17);
  srand(time(0));

  //initialize all parameters
  parse_arguments(argc, argv, data_s,query_s, k, L, out_s, stats, func, hash);
  input_parameters(data_s, func, hash);

  //data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;
  // for(int i=0; i<2; i++){
  //   cout << "Printing some curves!" << endl;
  //   curves[i].print();
  // }

  //return 1;

  // cout << data_s << endl << query_s << endl << out_s << endl;
  // cout << func << endl << hash << endl;

  //minimum of curve points
  //int minm{2};
  //float r{0.2};
  //delta = 4*dimension*minm*r;
  delta = 0.05;
  //cout <<"For delta= "<<delta <<'\n';

  vector<curve> normalized_curves{};

  for(unsigned int i=0; i<curves.size(); i++)
    normalized_curves.push_back(curve_reduction(curves[i],delta));

  //find min,max of curve points
  int min{},max{};
  min=max=normalized_curves[0].get_points().size();
  for(int i=1;i<normalized_curves.size();i++){
    if(normalized_curves[i].get_points().size()>max)
      max=normalized_curves[i].get_points().size();
    else if (normalized_curves[i].get_points().size()<min)
      min=normalized_curves[i].get_points().size();
  }

  //cout <<"max="<<max<<"\nmin="<<min<<endl;

  for(int Lrep=0; Lrep<L; Lrep++){//for L repetitions
    vector<curve> concat_curves{};
    for(unsigned int i=0; i<normalized_curves.size(); i++){//init concat_curve_points
      curve moved_curve(normalized_curves[i].get_dimension());
      moved_curve.set_id(normalized_curves[i].get_id());
      concat_curves.push_back(move(moved_curve));
    }
    for(int krep=0; krep<k; krep++){
      t.clear();
      //let's choose a t...
      chosen_t(delta,dimension,t);
      //cout << "t= (";
      //for(int i=0;i<dimension;i++){
      //  cout <<t[i] << " ";
      //}
      //cout <<")"<<'\n';
      for(unsigned int i=0; i<normalized_curves.size(); i++){//for every norm curve...
        vector<vector<double>> moved_points{};
        curve_move(normalized_curves[i].get_points(), t, dimension, max, moved_points);
        for(unsigned int j=0; j<moved_points.size(); j++){
          concat_curves[i].set_point(move(moved_points[j]));
          moved_points[j].clear();
        }
      }
    }
    //concat_curves[0].print();
  }
  return 1;
}
