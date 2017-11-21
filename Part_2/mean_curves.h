#ifndef MEAN_CURVES_H
#define MEAN_CURVES_H

#include <vector>

int minIndex(double a, double b ,double c);

void find_mean(const std::vector<std::vector<double>> & pointsA,
  const std::vector<std::vector<double>> & pointsB,
  std::vector<std::vector<double>> & pointsMean);

#endif
