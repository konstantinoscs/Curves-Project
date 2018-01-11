#include <iostream>
#include <string>
#include <ctime>

#include "../lib/curve.h"
#include "../lib/initialization.h"
#include "../lib/assignment.h"
#include "../lib/update.h"
#include "../lib/silhouette.h"
#include "../lib/distance_f.h"
#include "ro_data_ops.h"
#include "road.h"
#include "xml_ops.h"

using namespace std;

int main(int argc, char **argv){
  bool parse{false};
  string dist{"DFT2"},out_s{"kmedoid_ways_frechet.dat"};
  vector<way> ways;
  vector<vector<segment>> segments;
  string data_s{"Roads/segments.csv"}, way_s{"Roads/athens.csv"};
  parse_arguments(argc, argv, parse, dist);
  clock_t t = clock();
  if(dist=="DTW2") out_s = "kmedoid_ways_dtw.dat";
  if(parse){
    string xml_s{"Roads/athens_greece.osm"};
    vector<road> roads;
    vector<node> nodes;
    parse_xml(roads, nodes, xml_s);
    t = clock() -t;
    cout << "Parsing time: " << float(t)/CLOCKS_PER_SEC << '\n';
    //cout << roads.size() << '\n';
    //cout << nodes.size() << endl;
    t = clock();
    make_segments(roads, nodes);
    t = clock() -t;
    cout << "Segmenting time: " << float(t)/CLOCKS_PER_SEC << '\n';
  }
  t=clock();
  ways = read_ways(way_s);
  segments = read_data_segs(data_s, ways);
  dist.erase(3);
  t=clock() -t;
  cout << "Parsing segments time: " << float(t)/CLOCKS_PER_SEC << '\n';
//---------------
  int k{},a{};
  for(size_t i=0; i<segments.size(); i++){
    int segsize = (int)segments[i].size();
    if(segsize > 200) segsize = 200;
    //starting clustering for every segment type :)
    if(segsize < 500) a = 30;
    else if(segsize < 2000)  a = 50;
    else a = 80;
    vector<real_curve*> segs{},segs_all{},centroids{},prev_centroids{};
    for(size_t q=0; q<segments[i].size(); q++){
      segs.push_back(&segments[i][q]);
      segs_all.push_back(&segments[i][q]);
    }

    double k_sil[3]{};//to find best k with
    int k_best[3] = {3,segsize/2,-1};//binary way --> [first,last,mean]
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
      random_init(segs,k,centroids);// <----- 1
cout << "init OK" << endl;
      for(int j=0; j<k; j++)
        assign_sizes[j]=0;
      while(1){//assignment<-->update
        assigned_objects.clear();
        assigned_objects.resize(k);
        for(int j=0; j<k; j++)
          prev_assign_sizes[j]=assign_sizes[j];
        objf = lloyds_assignment(centroids,segs_all,dist,assigned_objects);// <----- 2
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
        //write_results(out_s,k,assigned_objects,Stotal);// <----- 5
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
