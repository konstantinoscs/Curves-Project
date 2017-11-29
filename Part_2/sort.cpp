#include <vector>

#include "curve.h"

using namespace std;

int partfunc(vector<real_curve *> & sortme, int left, int right, int pivot){
  int leftP{left},rightP{right-1};
  real_curve* temp{};
  while(1){
    while(stoi(sortme[leftP]->get_id()) < pivot && leftP<right) leftP++; 
    while(stoi(sortme[rightP]->get_id()) > pivot && rightP>left) rightP--;

    if(leftP>=rightP) break;
    else{
      temp = sortme[leftP];
      sortme[leftP] = sortme[rightP];
      sortme[rightP] = temp;
    }
    leftP++;
    rightP--;
  }
  temp = sortme[leftP];
  sortme[leftP] = sortme[right];
  sortme[right] = temp;
  return leftP;
}

int partfunc(vector<real_curve *> & sortme,
  vector<vector<real_curve *>> & followswap, int left, int right, int pivot){
  int leftP{left},rightP{right-1};
  real_curve *temp{};
  while(1){
    while(stoi(sortme[leftP]->get_id()) < pivot && leftP<right) leftP++;
    while(stoi(sortme[rightP]->get_id()) > pivot && rightP>left) rightP--;

    if(leftP>=rightP) break;
    else{
      temp = sortme[leftP];
      sortme[leftP] = sortme[rightP];
      sortme[rightP] = temp;
      followswap[leftP++].swap(followswap[rightP--]);
    }
  }
  temp = sortme[leftP];
  sortme[leftP] = sortme[right];
  sortme[right] = temp;
  followswap[leftP].swap(followswap[right]);
  return leftP;
}

void quicksort(vector<real_curve *> & sortme, int left, int right){
  if(right<=left) return ;
  int pivot{stoi(sortme[right]->get_id())};
  int partition = partfunc(sortme,left,right,pivot);
  quicksort(sortme, left, partition-1);
  quicksort(sortme, partition+1, right);
}

void quicksort(vector<real_curve *> & sortme,
  vector<vector<real_curve *>> & followswap, int left, int right){
  if(right-left<=0) return ;
  int pivot{stoi(sortme[right]->get_id())};
  int partition = partfunc(sortme, followswap, left, right, pivot);
  quicksort(sortme, followswap, left, partition-1);
  quicksort(sortme, followswap, partition+1, right);
}

void sort_clusters(vector<real_curve *> & centroids,
  vector<vector<real_curve *>> & assignment, int x){

  for(unsigned int i=0; i<centroids.size(); i++)
    quicksort(assignment[i],0,assignment[i].size()-1);

  if(x)//if not frechet update
    quicksort(centroids, assignment, 0, centroids.size()-1);
}
