#ifndef DISTANCE_OPS_H
#define DISTANCE_OPS_H

#include <vector>
#include <string>

//returns the euclidean distance between p1 and p2
double euclid_dist(const std::vector<double> & p1,
	const std::vector<double> & p2);

//computes the Discrete Frechet Distance 
void computeDFD(const std::vector<std::vector<double>> & pointsA,
	const std::vector<std::vector<double>> & pointsB,
	double & distance//returns the result here [output]
);

//computes the Dynamic Time Warping
void computeDTW(const std::vector<std::vector<double>> & pointsA,
	const std::vector<std::vector<double>> & pointsB,
	double & distance//returns the result here [output]
);

void find_distance(const std::vector<std::vector<double>> & pointsA,
	const std::vector<std::vector<double>> & pointsB,
	std::string dist,//choose the distance function from here
	double & distance//returns the distance between pA-pB here [output]
);

#endif
