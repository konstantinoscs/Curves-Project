#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct node {
  string id;
  double lat;
  double lon;
};

bool parse_xml(string data_s){
  ifstream data(data_s);
  vector<node> nodes;
  string temp{};
  max = std::numeric_limits<int>;
  //ignore the first 3 lines of the xml file
  data.ignore(max, '\n');
  data.ignore(max, '\n');
  data.ignore(max, '\n');


}
