#include <vector>
#include <iostream>
#include "classic_hash.h"
#include "curve_ops.h"
#include "distance_ops.h"
#include "curve.h"

using namespace std;

void find_nn(real_curve & scurve,vector<real_curve*> pcurves,
	int dimension, string dist, real_curve* & nneigh, double & distance){

	double temp_distance{};
//initialize distance with first curve's distance
	find_distance(scurve.get_points(),pcurves[0]->get_points(),dist,distance);
	nneigh = pcurves[0];
	for(int i=1; i<pcurves.size(); i++){
		find_distance(scurve.get_points(),pcurves[i]->get_points(),
			dist,temp_distance);
		if(temp_distance<distance){
			distance = temp_distance;
			nneigh = pcurves[i];
		}
	}
	return ;
}


void search_curves(vector<real_curve> & s_curves,
  vector<vector<vector<vector<real_curve*>>>> & Lht,int k, int v_size,
  int dimension, int delta, int tablesize, string hash,
	string dist, vector<real_curve*> & pcurves,
	real_curve** nn_curve,double* nn_distance,
	bool* grid_curve_found){

  vector<vector<norm_curve>> concat_s_curves{};
	vector<real_curve> n_curves{};//normalized_curves
	int tsize = s_curves.size();
	vector<real_curve*> same_grid_curves[tsize];
	vector<real_curve*> bucket_curves[tsize];
  vector<int> r{};
  int key{};
	double distance{};
  vector<int> curve_keys{};
	for(int i=0; i<s_curves.size(); i++){
		grid_curve_found[i]=false;
		//same_grid_curves.push_back({});//init with s_curves.size() empty vectors
		//bucket_curves.push_back({});
	}

//k-concatenate the search curves
  Lconcatenate_kcurves(k,1,s_curves,dimension,delta,concat_s_curves,
    v_size,n_curves);
  init_r(dimension*v_size*k,r);//if hash=="lsh" use first k elements of r
//find the key for every search curve...
//  if(hash=="classic"){
    for(int i=0; i<s_curves.size(); i++){
      linear_combination(concat_s_curves[0][i].as_vector(),r,key,tablesize);
      curve_keys.push_back(key);
    }
//  }
//  else if(hash=="lsh"){
//  }
//saves all curves in same bucket with s_curve[i]
  for(int i=0; i<s_curves.size(); i++){
    for(int j=0; j<Lht.size(); j++){
			for(int z=0; z<Lht[j][curve_keys[i]].size(); z++){
				if(n_curves[i].get_points()==Lht[j][curve_keys[i]][z][1]->get_points())
				{//then we found the same grid curve...
					grid_curve_found[i]=true;
					same_grid_curves[i].push_back(Lht[j][curve_keys[i]][z][0]);
				}
				bucket_curves[i].push_back(Lht[j][curve_keys[i]][z][0]);
			}
    }
  }
//let's find (probabilistic) nearest neighbor...
	real_curve* nneigh{};
	for(int i=0; i<s_curves.size(); i++){
		if(bucket_curves[i].size()==0)//hash tables were empty for i's key
			find_nn(s_curves[i],pcurves,dimension,dist,nneigh,distance);//search greedy
		else if(grid_curve_found[i])//search only in same grid curves
			find_nn(s_curves[i],same_grid_curves[i],dimension,dist,nneigh,distance);
		else//search in bucket curves
			find_nn(s_curves[i],bucket_curves[i],dimension,dist,nneigh,distance);
		nn_curve[i] = nneigh;
		nn_distance[i] = distance;
	}
	return ;
}

