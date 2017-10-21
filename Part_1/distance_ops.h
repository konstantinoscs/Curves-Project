#include <vector>
#include <string>

double euclid_dist(const std::vector<double> & p1,
	const std::vector<double> & p2);

void computeDFD(const std::vector<std::vector<double>> & pointsA,
	const std::vector<std::vector<double>> & pointsB, double & distance);

void computeDTW(const std::vector<std::vector<double>> & pointsA,
	const std::vector<std::vector<double>> & pointsB, double & distance);

void find_distance(const std::vector<std::vector<double>> & pointsA,
	const std::vector<std::vector<double>> & pointsB, std::string dist,
	double & distance);
