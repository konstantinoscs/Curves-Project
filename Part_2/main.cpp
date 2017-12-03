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
#include "silhouette.h"
#include "sort.h"

using namespace std;

int main(int argc, char **argv){
  int c{4}, L{3}, k{2}, kvec{4}, w{4};
  int dimension{};
  string input_s{}, config_s{}, out_s{"results"};
  string dist{};
  bool complete{false};
  //our curves aka the dataset
  vector<real_curve> curves{};
  vector<real_curve*> pcurves{}, centroids{}, pcurves_all{};
  clock_t begin, end;
  srand(time(0));

  parse_arguments(argc, argv, input_s, config_s, out_s, dist);
  parse_config(config_s, c, L, k);

  input_s = "./trajectories_dataset";        //for testing purposes
  if(!read_dataset_curves(input_s, curves, dimension)){
    cerr << "Something went wrong while reading the dataset!"<< endl;
    return -1;
  }

  cout << "Dataset read successfully!" << endl;
  cout << "Read " << curves.size() << " curves" << endl;

  if((int)curves.size()<c){
    cerr << "Centroids can't be more than curves!" << endl;
    return -1;
  }

  ofstream out_f(out_s);

  vector<assign_entry> entries;//for range assign
  init_assign_entries(entries, curves);//init entries
  for(unsigned int i=0; i<curves.size(); i++){
    pcurves.push_back(&curves[i]);
    pcurves_all.push_back(&curves[i]);
  }

  double delta = 0.06;
  int tablesize = curves.size()/4;
  int a;//mult with c and will be the
  if(curves.size() < 500) a = c + (c%2-1);
  else if(curves.size() < 2000)  a = 2*c + 1;
  else a = 3*c + (c%2-1);
  vector<vector<vector<assign_entry*>>> Lhashtable;

  init_hashtable(L, k, entries, dimension, delta, kvec, w, curves,
    tablesize,Lhashtable);
  cout << "Hashtable just initialized!" << endl;

//variables for main loop
  double objf{} ,time{};
  int assign_sizes[c],prev_assign_sizes[c];
  int changes{};
  vector<double> Si{};
  double Stotal;
  int flag{1};//used to create keys from 2nd rep(in while) for mean centroid
  vector<vector<int>> keys{};//for range assign
  vector<vector<real_curve*>> assigned_objects{};//assignment
  vector<real_curve*> prev_centroids{};//to check when to stop
  prev_centroids.resize(c);
  for(int i=0; i<2; i++){//for inits
    for(int j=0; j<1; j++){//for assigns
      for(int z=1; z<2; z++){//for updates
        if(!z && dist=="DTW") continue;//for DTW only PAM
        cout << "rep " << (4*i+2*j+z+1) << ":" << endl;
        begin = clock();//start clock
        if(i)//i=1
          kmeans_init(pcurves, c, centroids, dist);
        else//i=0
          random_init(pcurves, c, centroids);
        cout << "init:OK" << endl;
        for(int u=0; u<c; u++)
          assign_sizes[u]=0;
        flag = 1;
        while(1){//if small-(no) update break
          assigned_objects.clear();
          assigned_objects.resize(c);
          for(int t=0; t<c; t++)//saves last assign sizes
            prev_assign_sizes[t]=assign_sizes[t];
          if(j){//assignment here changes "assigned_objects"
            init_assign_entries(entries, curves);//init entries
            if(z || flag)
              find_keys(Lhashtable, centroids, keys);//pam or mean's first rep
            else
              create_mean_keys(w, k, dimension, tablesize, L, centroids, delta, keys);//2nd rep++ on mean
            flag = 0;
            objf = assign_by_range_search(centroids, Lhashtable, entries, keys, dist, assigned_objects);//j=1
          }
          else
            objf = lloyds_assignment(centroids, pcurves_all, dist, assigned_objects);//j=0

          changes=0;
          for(int t=0; t<c; t++){//save previous centroids and assign sizes
            prev_centroids[t]=centroids[t];
            assign_sizes[t]=assigned_objects[t].size();
            changes += abs(assign_sizes[t]-prev_assign_sizes[t]);
          }
          if(changes < a) break;//(1)if just a(c) objects changed cluster-->litle update-->break

          if(z)//update here changes "centroids"
            pam_update(centroids, assigned_objects, objf, dist);//z=1
          else
            mean_discrete_frechet(centroids, assigned_objects);//z=0

          if(prev_centroids == centroids) break;//(2)no update
          cout << endl;
        }
        compute_silhuette(centroids, assigned_objects, dist, Si, Stotal);
        if(complete)//update=mean frechet(z=0)->don't sort centroids
          sort_clusters(centroids, assigned_objects, z);// else sort them
        end = clock();//stop clock
        time = double(end - begin) / CLOCKS_PER_SEC;
        cout << "Write results!" << endl;
        write_results(out_f, centroids, assigned_objects, Si, Stotal,
          i, j, z, dist, complete, time, dimension);
      }
    }
  }
  return 0;
}
