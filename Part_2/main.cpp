#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "data_ops.h"
#include "curve.h"
#include "initialization.h"

using namespace std;

int main(int argc, char **argv){
  int c{5};
  int dimension{};
  string data_s{}, query_s{}, out_s{"results"};
  //our curves aka the dataset
  vector<real_curve> curves{};
  vector<real_curve*> pcurves{},centroids{};
  cout << std::fixed;
  cout << std::setprecision(17);
  srand(time(0));

  data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
    return -1;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;

  pcurves.clear();
  for(unsigned int i=0; i<curves.size(); i++)
		pcurves.push_back(&curves[i]);

  random_init(pcurves,c,centroids);
  //kmeans_init(pcurves,c,centroids,"DFT");

  //test:print the c centroids
  for(unsigned int i=0; i<centroids.size(); i++)
    cout <<"centroid "<<i<<":"<<centroids[i]->get_id()<<endl;

  return 0;
}

