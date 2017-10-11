#include "curve.h"
#include <vector>

using namespace std;

curve::curve(int dim): dimension(dim){

}

curve::~curve(){

}

void curve::set_id(string r_id){
    id = r_id;
}

string curve::get_id(){
  return id;
}

int curve::get_dimension(){
  return dimension;
}
