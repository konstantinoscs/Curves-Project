#include <vector>
#include <string>

using namespace std;

void find_distance(const vector<vector<double>> & pointsA,
	const vector<vector<double>> & pointsB, string dist, double & distance){
	
	if(dist=="DFT")
		distance = 3.0;
	else if(dist=="DTW")
		distance = 4.0;
	else 
		distance = 5.0;
//	else if(dist=="..something else..")

	return ;
}
