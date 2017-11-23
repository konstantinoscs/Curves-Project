#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

#include "data_ops.h"
#include "curve.h"
#include "initialization.h"
#include "assign_entry.h"
#include "range_assign.h"
#include "hashtable_init.h"
#include "assignment.h"

using namespace std;

int main(int argc, char **argv){
  int c{5}, L{3}, k{2}, kvec{4}, w{4};
  int dimension{};
  string data_s{}, query_s{}, out_s{"results"};
  string dist{"DFT"};
  //our curves aka the dataset
  vector<real_curve> curves{};
  vector<real_curve*> pcurves{}, centroids{}, pcurves_all{};
  clock_t begin, end;
  srand(time(0));

  data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
    return -1;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;

  for(unsigned int i=0; i<curves.size(); i++){
    pcurves.push_back(&curves[i]);
    pcurves_all.push_back(&curves[i]);
  }

  random_init(pcurves, c, centroids);
  //kmeans_init(pcurves,c,centroids,"DFT");

  vector<assign_entry> entries;
  init_assign_entries(entries, curves);//init entries

  double delta = 0.06;
  int tablesize = curves.size()/16;
  vector<vector<vector<assign_entry*>>> Lhashtable;

  init_hashtable(L, k, entries, dimension, delta, kvec, w, curves,
    tablesize,Lhashtable);
  cout << "Hashtable just initialized!" << endl;
  begin = clock();
  vector<vector<int>> keys{};
  find_keys(Lhashtable, centroids, keys);

  vector<vector<real_curve*>> assigned_objects{};
  assigned_objects.resize(c);
  double objf{0.0};
  objf = assign_by_range_search(centroids, Lhashtable, entries, keys, dist, assigned_objects);
  end = clock();
  //test keys
  for(int i=0; i<c; i++){
    cout << "for " << centroids[i]->get_id() << ":";
    for(int j=0; j<L; j++){
      int aaa = Lhashtable[j][keys[i][j]].size();
      cout << " " << keys[i][j] << "(" << aaa << ")";
    }
    cout << "-->" << assigned_objects[i].size() << endl;
  }
  cout <<"range:"<< (double(end - begin) / CLOCKS_PER_SEC) << "--" << objf << endl;

  begin = clock();
  assigned_objects.clear();
  assigned_objects.resize(c);
  objf = 0;
  objf = lloyds_assignment(centroids, pcurves_all, dist, assigned_objects);
  end = clock();
  for(int i=0; i<c; i++){
    cout << "for " << centroids[i]->get_id() << ":";
    cout << "-->" << assigned_objects[i].size() << endl;
  }
  cout <<"lloyds:"<< (double(end - begin) / CLOCKS_PER_SEC) << "--" << objf  << endl;
  return 0;
}
