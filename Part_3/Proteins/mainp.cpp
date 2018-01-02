#include <iostream>
#include <string>
#include <vector>

#include "pr_data_ops.h"
#include "../lib/curve.h"

using namespace std;

int main(void){
  int numConform{},N{};
  string input="bio_small_input.dat";
  vector<real_curve> proteins{};
  parse_config(input,numConform,N,proteins);
  cout << "Protein's dataset read successfully!" << endl;
  cout << "numConform=" << numConform <<endl;
  cout << "N=" << N << endl;

//  for(int i=0;i<3;i++)
//    cout << proteins[0].get_points()[9][i]  << " ";
//  cout << endl;

  return 0;
}
