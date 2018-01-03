#include <iostream>
#include <string>
#include <vector>

#include "pr_data_ops.h"
#include "distance_f.h"
#include "../lib/curve.h"
#include "../lib/Eigen/Dense"

using namespace Eigen;
using namespace std;

int main(void){
  int numConform{},N{};
  string input="bio_small_input.dat";
  vector<real_curve> proteins{};
  parse_config(input,numConform,N,proteins);
  cout << "Protein's dataset read successfully!" << endl;
  cout << "numConform=" << numConform <<endl;
  cout << "N=" << N << endl;

  cout << pr_cRMSD(proteins[0].get_points(),proteins[10].get_points(),N) << endl;
  cout << pr_frechet(proteins[0].get_points(),proteins[10].get_points(),N) << endl;
//  for(int i=0;i<3;i++)
//    cout << proteins[0].get_points()[9][i]  << " ";
//  cout << endl;

  return 0;
}
