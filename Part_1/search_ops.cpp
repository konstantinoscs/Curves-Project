#include <vector>
#include "classic_hash.h"
#include "curve_ops.h"
#include "curve.h"

using namespace std;

void search_curves(vector<real_curve> & s_curves,
  vector<vector<vector<vector<real_curve*>>>> & Lht,int k, int v_size,
  int dimension, int delta, int tablesize, string hash){

    vector<vector<norm_curve>> concat_s_curves{};
		vector<real_curve> normalized_curves{};
    vector<int> r{};
    int key{},flag{};
    vector<int> curve_keys{};
    vector<bool> grid_curve_found{};
		for(int i=0; i<s_curves.size(); i++)
			grid_curve_found.push_back(false);

//k-concatenate the search curves
    Lconcatenate_kcurves(k,1,s_curves,dimension,delta,concat_s_curves,
      v_size,normalized_curves);
    init_r(dimension*v_size*k,r);//if hash=="lsh" use first k elements of r
//find the key for every search curve...
//    if(hash=="classic"){
      for(int i=0; i<s_curves.size(); i++){
        linear_combination(concat_s_curves[0][i].as_vector(),r,key,tablesize);
        curve_keys.push_back(key);
      }
//    }
//    else if(hash=="lsh"){
//    }
//search for nearest neighbor
    for(int i=0; i<s_curves.size(); i++){
      flag = 0;//if the L ht[key] are empty we'll search greedy
      for(int j=0; j<Lht.size(); j++){
				for(int z=0; z<Lht[j][curve_keys[i]].size(); z++){
					flag = 1;//ht[key] not empty
					
				}
      }
    }


}
