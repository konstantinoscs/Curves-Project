#include <vector>

#include "curve.h"

using namespace std;

void swap(real_curve * x, real_curve * y){
  real_curve *temp=x;
  x = y;
  y = temp;
}

void swap(vector<real_curve *> x, vector<real_curve *> y){
  x.swap(y);
}

int partfunc(vector<real_curve *> & sortme, int left, int right, string pivot){
  int leftP{left},rightP{right-1};
  while(1){
    while(sortme[leftP]->get_id().compare(pivot)<0) leftP++;

    while(sortme[rightP]->get_id().compare(pivot)>0) rightP++;

    if(leftP>=rightP) break;
    else swap(sortme[leftP++],sortme[rightP--]);
  }

  swap(sortme[leftP],sortme[right]);
  return leftP;
}

int partfunc(vector<real_curve *> & sortme,
  vector<vector<real_curve *>> & followswap, int left, int right, string pivot){
  int leftP{left},rightP{right-1};
  while(1){
    while(sortme[leftP]->get_id().compare(pivot)<0) leftP++;

    while(sortme[rightP]->get_id().compare(pivot)>0) rightP++;

    if(leftP>=rightP) break;
    else{
      swap(sortme[leftP],sortme[rightP]);
      swap(followswap[leftP++],followswap[rightP--]);
    }
  }

  swap(sortme[leftP],sortme[right]);
  swap(followswap[leftP],followswap[right]);
  return leftP;
}

void quicksort_one(vector<real_curve *> & sortme, int left, int right){
  if(right-left<=0) return ;
  string pivot = sortme[right]->get_id();
  int partition = partfunc(sortme,left,right,pivot);
  quicksort_one(sortme, left, partition-1);
  quicksort_one(sortme, partition+1, right);
}

void quicksort_two(vector<real_curve *> & sortme,
  vector<vector<real_curve *>> & followswap, int left, int right){

  if(right-left<=0) return ;
  string pivot = sortme[right]->get_id();
  int partition = partfunc(sortme, followswap, left, right, pivot);
  quicksort_two(sortme, followswap, left, partition-1);
  quicksort_two(sortme, followswap, partition+1, right);
}

void sort_clusters(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment, int x){

  for(unsigned int i=0; i<centroids.size(); i++)
    quicksort_one(assignment[i],0,assignment[i].size()-1);

  if(!x)//if not frechet update
    quicksort_two(centroids, assignment, 0, centroids.size()-1);
}
