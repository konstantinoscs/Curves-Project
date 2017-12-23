#include <iostream>
#include <string>

struct node {
  string id;
  double lat;
  double lon;
}

bool parse_xml(string data_s){
  ifstream data(data_s);
  vector<node> nodes;
  

}
