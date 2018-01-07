#include <iostream>
#include <string>
#include <vector>

#include "pr_data_ops.h"
#include "../lib/distance_f.h"
#include "../lib/curve.h"
#include "../lib/initialization.h"
#include "../lib/assignment.h"
#include "../lib/update.h"
#include "../lib/silhouette.h"

using namespace std;

int main(int argc, char **argv){
  int numConform{},N{};
//  string input{"bio_small_input.dat"};
  string input{};
  vector<real_curve> proteins{};

  if(!parse_arguments(argc, argv, input)){
    cerr << "Input file not found!" << endl;
    return -1;
  }
  if(!parse_input(input,numConform,N,proteins)){
    cerr << "Something went wrong while reading the dataset!" << endl;
    return -1;
  }

  cout << "Protein's dataset read successfully!" << endl;
  cout << "numConform=" << numConform <<endl;
  cout << "N=" << N << endl;
  vector<real_curve*> pproteins{},pproteins_all{},centroids{},prev_centroids{};
  for(int i=0; i<numConform; i++){
    pproteins.push_back(&proteins[i]);
    pproteins_all.push_back(&proteins[i]);
  }

  string dist{"cRMSD"},out_s{"crmsd.dat"};
  int a{},k{};
  for(int t=0; t<2; t++){//for questions A and B(just change the dist...)
    if(t){ dist = "frechet"; out_s = "frechet.dat"; cout << "Starting B..." << endl;}// for B
    else cout << "Starting A..." << endl;

    double k_sil[3]{};//to find best k with
    int k_best[3] = {2,numConform/2,-1};//logarithmic way --> [first,last,mean]
    int index{};//array's index to get current k

    double Stotal{-2};//Stotal in [-1,1],init with something < -1
    int changes{};
    vector<double> Si{};
    double tempStotal{},objf{};
    vector<int> assign_sizes{},prev_assign_sizes{};
    vector<vector<real_curve*>> assigned_objects{};//assignment
    while((k_best[1]-k_best[0]>1) || k_best[2]<=0){//check some k for clusters
      if(k_best[2]==-1){k=k_best[0];k_best[2]++;index=0;}//--------------------
      else if(k_best[2]==0){k=k_best[1];k_best[2]++;index=1;}//-----set k------
      else {k=(k_best[0]+k_best[1])/2;k_best[2]=k;index=2;}//------------------
cout << "Checking with k=" << k << endl;
      centroids.clear();
      centroids.resize(k);
      prev_centroids.clear();
      prev_centroids.resize(k);
      assign_sizes.clear();
      assign_sizes.resize(k);
      prev_assign_sizes.clear();
      prev_assign_sizes.resize(k);
      if(numConform < 500) a = k + (k%2-1);
      else if(numConform < 2000)  a = 2*k + 1;
      else a = 3*k + (k%2-1);
      random_init(pproteins,k,centroids);// <----- 1
cout << "init OK" << endl;
      for(int j=0; j<k; j++)
        assign_sizes[j]=0;
      while(1){//assignment<-->update
        assigned_objects.clear();
        assigned_objects.resize(k);
        for(int j=0; j<k; j++)
          prev_assign_sizes[j]=assign_sizes[j];
        objf = lloyds_assignment(centroids,pproteins_all,dist,assigned_objects);// <----- 2
cout << "assignment OK" << endl;
        changes = 0;
        for(int j=0; j<k; j++){
          prev_centroids[j] = centroids[j];
          assign_sizes[j] = assigned_objects[j].size();
          changes += abs(assign_sizes[j]-prev_assign_sizes[j]);
        }
        if(changes < a) break;
        pam_update(centroids,assigned_objects,objf,dist);// <----- 3
cout << "update OK" << endl;
        if(prev_centroids == centroids) break;
      }
cout << "Computing silhuette..." << endl;
      compute_silhuette(centroids, assigned_objects, dist, Si, tempStotal);// <----- 4
cout <<"(for k=" << k << " silhuette=" << tempStotal << ")" << endl;
      if(tempStotal > Stotal){
        Stotal = tempStotal;
cout << "writing results..." << endl;
        write_results(out_s,k,assigned_objects,Stotal);// <----- 5
      }

      k_sil[index] = tempStotal;//set silhuettes
      if(index==2){//swap first or last with mean k
        if(k_sil[1]>k_sil[0]){k_best[0]=k_best[2];k_sil[0]=k_sil[2];}
        else{k_best[1]=k_best[2];k_sil[1]=k_sil[2];}
      }
    }
  }
  return 0;
}
