#include <iostream>
#include <string>

#include "xml_ops.h"

using namespace std;

int main(int argc, char **argv){
  string data_s{"athens_greece.osm"};
  parse_xml(data_s);
}
