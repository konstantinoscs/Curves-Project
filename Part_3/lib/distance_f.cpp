#include<iostream>
#include <cmath>
#include <limits>

#include "Eigen/Dense"
#include "distance_ops.h"

using namespace Eigen;
using namespace std;

double pr_cRMSD( vector<vector<double>> X0, vector<vector<double>> Y0, int N){
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
    for(int x=0;x<3;x++){
      X(i,x) = X0[i][x] - Xc[x];
      Y(i,x) = Y0[i][x] - Yc[x];
    }
  }
  JacobiSVD<MatrixXd> svd(X.transpose()*Y,ComputeThinU | ComputeThinV);
  JacobiSVD<MatrixXd>::SingularValuesType singular = svd.singularValues();
  if(singular(2)<=0) return std::numeric_limits<double>::max();//don't choose this distance
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

double pr_frechet( vector<vector<double>> X0, vector<vector<double>> Y0, int N){
  if(X0.size()!=Y0.size()) return std::numeric_limits<double>::max();
  double Xc[3],Yc[3];
  double dist{};
  for(int i=0; i<N; i++){
    if(X0[i].size()==2){X0[i].push_back(0.0);Y0[i].push_back(0.0);}
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
    for(int x=0;x<3;x++){
      X(i,x) = X0[i][x] - Xc[x];
      Y(i,x) = Y0[i][x] - Yc[x];
    }
  }
  JacobiSVD<MatrixXd> svd(X.transpose()*Y,ComputeFullU | ComputeFullV);
  JacobiSVD<MatrixXd>::SingularValuesType singular = svd.singularValues();
  if(singular(2)<=0) return std::numeric_limits<double>::max();//don't choose this distance
  MatrixXd Q = svd.matrixU() * svd.matrixV().transpose();
  if(Q.determinant()<0){
    MatrixXd tempU = svd.matrixU();
    tempU(0,2)*=-1;
    tempU(1,2)*=-1;
    tempU(2,2)*=-1;
    Q = tempU * svd.matrixV().transpose();
  }
  MatrixXd X1 = X * Q;
  vector<vector<double>> A{},B{};//save XQ in A, Y in B to call computeDFD
  A.resize(N);
  B.resize(N);
  for(int i=0; i<N; i++){//A and B are N x 3 arrays
    for(int j=0; j<3; j++){
      A[i].push_back(X1(i,j));
      B[i].push_back(Y(i,j));
    }
  }
  computeDFD( A, B, dist);
  return dist;
}

double pr_dtw( vector<vector<double>> X0, vector<vector<double>> Y0, int N){
  if(X0.size()!=Y0.size()) return std::numeric_limits<double>::max();
  double Xc[3],Yc[3];
  double dist{};
  for(int i=0; i<N; i++){
    if(X0[i].size()==2){X0[i].push_back(0.0);Y0[i].push_back(0.0);}
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
    for(int x=0;x<3;x++){
      X(i,x) = X0[i][x] - Xc[x];
      Y(i,x) = Y0[i][x] - Yc[x];
    }
  }
  JacobiSVD<MatrixXd> svd(X.transpose()*Y,ComputeFullU | ComputeFullV);
  JacobiSVD<MatrixXd>::SingularValuesType singular = svd.singularValues();
  if(singular(2)<=0) return std::numeric_limits<double>::max();;//don't choose this distance
  MatrixXd Q = svd.matrixU() * svd.matrixV().transpose();
  if(Q.determinant()<0){
    MatrixXd tempU = svd.matrixU();
    tempU(0,2)*=-1;
    tempU(1,2)*=-1;
    tempU(2,2)*=-1;
    Q = tempU * svd.matrixV().transpose();
  }
  MatrixXd X1 = X * Q;
  vector<vector<double>> A{},B{};//save XQ in A, Y in B to call computeDTW
  A.resize(N);
  B.resize(N);
  for(int i=0; i<N; i++){//A and B are N x 3 arrays
    for(int j=0; j<3; j++){
      A[i].push_back(X1(i,j));
      B[i].push_back(Y(i,j));
    }
  }
  computeDTW( A, Y0, dist);
  return dist;
}


