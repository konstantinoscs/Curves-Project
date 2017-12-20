#include <vector>
#include <limits>
#include <iostream>

#include "curve.h"
#include "distance_ops.h"
#include "minmax.h"

using namespace std;

int minIndex(double a, double b ,double c){
  if(a<b && a<c)
    return 0;//a is min
  if(b<c)//a sure not min,check only b,c
    return 1;//b is min
  return 2;//c is min--->returns 2 if a=b=c
}

real_curve * find_mean(const real_curve * curveA,
  const real_curve * curveB){
  const vector<vector<double>> & pointsA = curveA->get_points();
  const vector<vector<double>> & pointsB = curveB->get_points();
  vector<double> point{};//every mean's point
  int m=pointsA.size(), n=pointsB.size();
  int P=m,Q=n;
  vector<vector<int>> index_path{{P,Q}};

  double ** L;
  L = new double*[m+1];
  for(int i=0; i<m+1; i++)
    L[i] = new double[n+1];
  double maxdbl{std::numeric_limits<double>::max()};
  real_curve * curveMean = new real_curve();
  curveMean->set_id("-1");
  curveMean->set_dimension(curveA->get_dimension());

  L[0][0]=0.0;
  for(int i=1; i<m+1; i++)
    L[i][0] = maxdbl;
  for(int i=1; i<n+1; i++)
    L[0][i] = maxdbl;
  for(int i=1; i<m+1; i++)
    for(int j=1; j<n+1; j++)
      L[i][j] = MYmax(euclid_dist(pointsA[i-1],pointsB[j-1]),
                  MYmin(L[i-1][j-1],MYmin(L[i-1][j],L[i][j-1])));
  int minidx;
  while(P!=1 || Q!=1){
    minidx = minIndex(L[P-1][Q],L[P][Q-1],L[P-1][Q-1]);
    if(minidx==0)
      index_path.push_back({--P,Q});//finding the reversed index vector
    else if(minidx==1)
      index_path.push_back({P,--Q});
    else
      index_path.push_back({--P,--Q});
  }
  vector<double> prev_point{};
  for(int i=0;i<curveA->get_dimension();i++)//init prev_point
    prev_point.push_back(maxdbl);
  int Msize = index_path.size();
  int counter{1};
  int flag{1};//when we have less than 600 points we push them all in mean
  if(Msize>600) flag=0;//else the points are too much so we skip some of them
  for(int i = Msize-1; i>=0; i--){
    for(unsigned int j=0; j<pointsA[index_path[i][0]-1].size(); j++)
      point.push_back((pointsA[index_path[i][0]-1][j] + pointsB[index_path[i][1]-1][j])/2);
    if(point!=prev_point){//insert in mean if not same point
      if(counter%3 || flag){//if Msize>600 keep 2/3 of points
        curveMean->set_point(std::move(point));
        prev_point=point;
        counter++;
      }
      else counter=1;
    }
    point.clear();
  }
  for(int i=0; i<m+1; i++)
    delete [] L[i];
  delete [] L;
  return curveMean;
}
