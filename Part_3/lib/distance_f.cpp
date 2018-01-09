#include<iostream>
#include <cmath>
#include <limits>

#include "Eigen/Dense"
#include "distance_ops.h"

using namespace Eigen;
using namespace std;

double pr_cRMSD(const vector<vector<double>> X0,const vector<vector<double>> Y0, int N){
  double Xc[3]{},Yc[3]{};
  for(int i=0; i<N; i++){
    for(int j=0; j<3; j++){
      Xc[j]+=X0[i][j];
      Yc[j]+=Y0[i][j];
    }
  }
  for(int j=0; j<3; j++){
    Xc[j]/=N;
    Yc[j]/=N;
  }
  MatrixXd X(N,3),Y(N,3);
  for(int i=0; i<N; i++){
    X(i,0) = X0[i][0] - Xc[0];
    X(i,1) = X0[i][1] - Xc[1];
    X(i,2) = X0[i][2] - Xc[2];
    Y(i,0) = Y0[i][0] - Yc[0];
    Y(i,1) = Y0[i][1] - Yc[1];
    Y(i,2) = Y0[i][2] - Yc[2];
  }
  JacobiSVD<MatrixXd> svd(X.transpose()*Y,ComputeThinU | ComputeThinV);
  JacobiSVD<MatrixXd>::SingularValuesType singular = svd.singularValues();
  if(singular(2)<=0) return std::numeric_limits<int>::max();//don't choose this distance
  MatrixXd Q = svd.matrixU() * svd.matrixV().transpose();
  if(Q.determinant()<0){
    MatrixXd tempU = svd.matrixU();
    tempU(0,2)*=-1;
    tempU(1,2)*=-1;
    tempU(2,2)*=-1;
    Q = tempU * svd.matrixV().transpose();
  }

  return (X*Q-Y).norm()/sqrt(N);
}

double pr_frechet(const vector<vector<double>> X0,const vector<vector<double>> Y0, int N){
  int no = X0[0].size();
  double Xc[no],Yc[no];
  double dist{};
  for(int i=0; i<N; i++){
    for(int j=0; j<no; j++){
      Xc[j]+=X0[i][j];
      Yc[j]+=Y0[i][j];
    }
  }
  for(int j=0; j<no; j++){
    Xc[j]/=N;
    Yc[j]/=N;
  }

  MatrixXd X(N,no),Y(N,no);
  for(int i=0; i<N; i++){
    for(int x=0;x<no;x++){
      X(i,x) = X0[i][x] - Xc[x];
      Y(i,x) = Y0[i][x] - Yc[x];
    }
  }
  JacobiSVD<MatrixXd> svd(X.transpose()*Y,ComputeFullU | ComputeFullV);
  JacobiSVD<MatrixXd>::SingularValuesType singular = svd.singularValues();
  if(singular(no-1)<=0) return 999;//don't choose this distance
  MatrixXd Q = svd.matrixU() * svd.matrixV().transpose();
  if(Q.determinant()<0){
    MatrixXd tempU = svd.matrixU();
    for(int x=0;x<no;x++)
      tempU(x,no-1)*=-1;
    Q = tempU * svd.matrixV().transpose();
  }
  MatrixXd X1 = X * Q;
  vector<vector<double>> A{},B{};//save XQ,Y in A,B to call computeDFD
  A.resize(N);
  B.resize(N);
  for(int i=0; i<N; i++){//A and B are N x 3 arrays
    for(int j=0; j<no; j++){
      A[i].push_back(X1(i,j));
      B[i].push_back(Y(i,j));
    }
  }
  computeDFD(X0, Y0, dist);
  return dist;
}

