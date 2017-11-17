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
#include "assign_entry.h"
#include "range_assign.h"

using namespace std;

int main(int argc, char **argv){
  int c{5},L{3},k{2},kvec{4},w{4};
  int dimension{};
  string data_s{}, query_s{}, out_s{"results"};
  //our curves aka the dataset
  vector<real_curve> curves{};
  vector<real_curve*> pcurves{}, centroids{};
  srand(time(0));

  data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
    return -1;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;

  for(unsigned int i=0; i<curves.size(); i++)
		pcurves.push_back(&curves[i]);

  random_init(pcurves, c, centroids);
  //kmeans_init(pcurves,c,centroids,"DFT");

  vector<assign_entry> entries;
  init_assign_entries(entries, curves);//init entries

  double delta = 0.08;
  int tablesize = curves.size()/32;
  vector<vector<vector<assign_entry*>>> Lhashtable;

  init_hashtable(L,k,entries,dimension,delta,kvec,w,curves,
    tablesize,Lhashtable);

  vector<vector<int>> keys{};
  find_keys(Lhashtable,centroids,keys);

  //test keys
  for(int i=0; i<c; i++){
    cout << "for " << centroids[i]->get_id() << ":";
    for(int j=0; j<L; j++){
      cout << " " << keys[i][j] ;
    }
    cout << endl;
  }

  return 0;
}
