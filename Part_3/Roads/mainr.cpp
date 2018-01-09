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
  vector<way> ways;
  vector<vector<segment>> segments;
  string data_s{"segments.csv"}, way_s{"athens.csv"};
  parse_arguments(argc, argv, parse);
  clock_t t = clock();
  if(parse){
    string xml_s{"athens_greece.osm"};
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
  t=clock() -t;
  cout << "Parsing segments time: " << float(t)/CLOCKS_PER_SEC << '\n';
//---------------
  int k{10},a{7};
  string dist{"frechet"};
  for(size_t i=0; i<segments.size(); i++){
    if(segments[i].size()>2000){cout <<"skip.."<<i<<endl;continue;}
    //starting clustering for every segment type :)
    vector<real_curve*> segs{},segs_all{},centroids{},prev_centroids{};
    for(int q=0; q<segments[i].size(); q++){
      segs.push_back(&segments[i][q]);
      segs_all.push_back(&segments[i][q]);
    }
    double Stotal{-2};//Stotal in [-1,1],init with something < -1
    int changes{};
    vector<double> Si{};
    double objf{};
    vector<int> assign_sizes{},prev_assign_sizes{};
    vector<vector<real_curve*>> assigned_objects{};//assignment
    centroids.resize(k);
    prev_centroids.resize(k);
    assign_sizes.resize(k);
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
      for(int f=0;f<k;f++)
cout <<"centr:"<<f<<"="<<centroids[f]->get_id()<<" with "<< centroids[f]->get_points().size() << " points!"<<endl;

    }
cout << "Computing silhuette..." << endl;
    compute_silhuette(centroids, assigned_objects, dist, Si, Stotal);// <----- 4
cout <<"Stotal="<<Stotal<<endl;
    //write_results(out_s,k,assigned_objects,Stotal);// <----- 5

  }
  
}
