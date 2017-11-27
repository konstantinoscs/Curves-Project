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
#include "update.h"

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
  double init_time{};
  srand(time(0));

  data_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(data_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
    return -1;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;
  vector<assign_entry> entries;//for range assign
  init_assign_entries(entries, curves);//init entries
  for(unsigned int i=0; i<curves.size(); i++){
    pcurves.push_back(&curves[i]);
    pcurves_all.push_back(&curves[i]);
  }

  double delta = 0.06;
  int tablesize = curves.size()/16;
  vector<vector<vector<assign_entry*>>> Lhashtable;

  init_hashtable(L, k, entries, dimension, delta, kvec, w, curves,
    tablesize,Lhashtable);
  cout << "Hashtable just initialized!" << endl;

//variables for main loop
  double objf{};
  int assign_sizes[c],prev_assign_sizes[c];
  for(int i=0; i<c; i++)
    assign_sizes[i]=0;
  int changes{};
  vector<vector<int>> keys{};//for range assign
  vector<vector<real_curve*>> assigned_objects{};//assignment
  vector<real_curve*> prev_centroids{};//to check when to stop
  prev_centroids.resize(c);
  for(int i=1; i<2; i++){//for inits
    begin = clock();
    if(i)//i=1
      kmeans_init(pcurves, c, centroids, dist);
    else//i=0
      random_init(pcurves, c, centroids);
    end = clock();
    init_time = double(end - begin) / CLOCKS_PER_SEC;
    for(int j=0; j<1; j++){//for assigns
      for(int z=0; z<1; z++){//for updates
        cout << "rep " << (4*i+2*j+z+1) << ":" << endl;
        cout << "init:OK (" << init_time << ")" << endl;
        while(1){//if small-(no) update break
          begin = clock();
          assigned_objects.clear();
          assigned_objects.resize(c);
          for(int t=0; t<c; t++)//saves last assign sizes
            prev_assign_sizes[t]=assign_sizes[t];
          if(j){//assignment here changes "assigned_objects"
            init_assign_entries(entries, curves);//init entries
            find_keys(Lhashtable, centroids, keys);
            objf = assign_by_range_search(centroids, Lhashtable, entries, keys, dist, assigned_objects);//j=1
          }
          else
            objf = lloyds_assignment(centroids, pcurves_all, dist, assigned_objects);//j=0
          end = clock();
          cout << "assignment:OK (" << (double(end - begin) / CLOCKS_PER_SEC) << ")" << endl;
          cout << "objf:" << objf << endl;
          changes=0;
          for(int t=0; t<c; t++){//save previous centroids and assign sizes
            prev_centroids[t]=centroids[t];
            assign_sizes[t]=assigned_objects[t].size();
            cout << "prev:" << prev_assign_sizes[t] << ",new:" << assign_sizes[t] << endl;
            changes += abs(assign_sizes[t]-prev_assign_sizes[t]);
          }
          if(changes < 5) break;//if just 2 objects changed cluster-->litle update-->break
          begin = clock();
          if(z)//update here changes "centroids"
            pam_update(centroids, assigned_objects, objf, dist);//z=1
          else
            mean_discrete_frechet(centroids, assigned_objects);//z=0
          end = clock();
          cout << "update:OK (" << (double(end - begin) / CLOCKS_PER_SEC) << ")" << endl;
          if(prev_centroids == centroids) break;
        }
        //output here :-)
      }
    }
  }
  return 0;
}
