#include <vector>
#include <ctime>

#include "general_hash.h"
#include "curve_ops.h"
#include "distance_ops.h"
#include "curve.h"
#include "entry.h"
#include "lsh.h"

using namespace std;

void find_nn(real_curve & scurve,vector<real_curve*> pcurves,
	int dimension, string dist, real_curve* & nneigh, double & distance,
	bool stats, double R, vector<string> & curves_in_R_i){

	double temp_distance{};
//initialize distance with first curve's distance
	find_distance(scurve.get_points(),pcurves[0]->get_points(),dist,distance);
	nneigh = pcurves[0];
	if(!stats && distance<=R)//if stats==false compare their distance to
			curves_in_R_i.push_back(pcurves[0]->get_id());//keep it's id (maybe)
	for(size_t i=1; i<pcurves.size(); i++){//for the rest curves...
		find_distance(scurve.get_points(),pcurves[i]->get_points(),
			dist,temp_distance);
		if(temp_distance<distance){//in the end we'll have in nneigh the
			distance = temp_distance;//nearest curve
			nneigh = pcurves[i];
		}
		if(!stats && temp_distance<=R)//again check if we'll keep curve's id
			curves_in_R_i.push_back(pcurves[i]->get_id());
	}
	//only if R=0 we put in "curves_in_R_i" the nearest curve's id
	if(!stats && R==0.0 && !(curves_in_R_i.size()))//maybe same curve(s) found
		curves_in_R_i.push_back(nneigh->get_id());//else push the nneigh
	return ;
}


void search_curves(vector<real_curve> & s_curves,
  vector<vector<vector<entry>>> & Lht, int k, int v_size,
  int dimension, double delta, int tablesize, string hash,
	string dist, vector<real_curve*> & pcurves, bool stats,
	double R, real_curve** nn_curve, double* nn_distance,
	bool* grid_curve_found, vector<string> * curves_in_R, int w,
	double* elapsed_time){

  vector<vector<norm_curve>> concat_s_curves{};
	vector<real_curve> n_curves{};//normalized_curves
	int tsize = s_curves.size();
	vector<real_curve*> same_grid_curves[tsize];
	vector<real_curve*> bucket_curves[tsize];
  vector<int> r{};
  int key{};
	double distance{};
  vector<int> curve_keys{};//has the key for every s_curve(after we find it)
  clock_t begin,end;
  
	for(size_t i=0; i<s_curves.size(); i++)
		grid_curve_found[i]=false;
  //k-concatenate the search curves
  Lconcatenate_kcurves(k,1,s_curves,dimension,delta,concat_s_curves,
    v_size,n_curves);
  init_r(dimension*v_size*k,r);//if hash=="lsh" use first k elements of r

  //find the key for every search curve...
  if(hash=="classic"){
    for(size_t i=0; i<s_curves.size(); i++){
      linear_combination(concat_s_curves[0][i].as_vector(),r,key,tablesize);
      curve_keys.push_back(key);
    }
  }
  else if(hash=="probabilistic"){//lsh
    vector<hash_f> hs;
    vector<int> g;
    make_hashes(hs, w, dimension, k);
    make_g(hs, g);
    for(size_t i=0; i<s_curves.size(); i++){
      vector<int> h_results{};
      for (size_t j=0; j<g.size(); j++)
        h_results.push_back(hs[g[j]].hash(concat_s_curves[0][i].as_vector()));
      linear_combination(h_results,r,key,tablesize);
      curve_keys.push_back(key);
      }
  }
  //creates here the vector which we'll search for nn
  for(size_t i=0; i<s_curves.size(); i++){
    for(size_t j=0; j<Lht.size(); j++){//looking in all (L) hashtables
    	//search in same bucket with s_curves[i]: 
			for(size_t z=0; z<Lht[j][curve_keys[i]].size(); z++){
				if(n_curves[i].get_points()==Lht[j][curve_keys[i]][z].gcurve->get_points())
				{//here we found the same grid curve...
					grid_curve_found[i] = true;
					same_grid_curves[i].push_back(Lht[j][curve_keys[i]][z].rcurve);
					//push the curve in vector to search first here if its not empty
				}
				bucket_curves[i].push_back(Lht[j][curve_keys[i]][z].rcurve);
				//second try:looking all curves in same bucket^^
				//else we search all curves for nn
			}
    }
  }
//let's find (probabilistic) nearest neighbor...
	real_curve* nneigh{};
	for(size_t i=0; i<s_curves.size(); i++){
		begin = clock();//starts counting the time
		if(bucket_curves[i].size()==0){//hash tables were empty for i's key
			//our last resolution:searching in all curves
			find_nn(s_curves[i],pcurves,dimension,dist,nneigh,
				distance,stats,R,curves_in_R[i]);//search greedy+in radius R
			stats = true;//use stats as flag to avoid calling second time this fnct
		}
		else if(same_grid_curves[i].size()!=0){
			//lucky:we found same grid curves so search in them
			find_nn(s_curves[i],same_grid_curves[i],dimension,dist,nneigh,
				distance,stats,R,curves_in_R[i]);//also check if their distance<=R
			stats = true;
		}
		else//search in bucket_curves
			find_nn(s_curves[i],bucket_curves[i],dimension,dist,nneigh,
				distance,true,0,curves_in_R[i]);
		nn_curve[i] = nneigh;
		nn_distance[i] = distance;
		if(!stats)//search in radius R
			//access here only if we search only in bucket_curves
			find_nn(s_curves[i],pcurves,dimension,dist,nneigh,
				distance,stats,R,curves_in_R[i]);
		end = clock();//counting ended
		elapsed_time[i] += double(end - begin) / CLOCKS_PER_SEC;
	}
	return ;
}
