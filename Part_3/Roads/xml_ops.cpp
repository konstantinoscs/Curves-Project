#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct node {
  string id;
  double lat;
  double lon;
  node();
  //move constructor
  node(node && mnode);
  //copy constructor in case move fails
  node(node & cnode);
  void print();
};

node::node():id(""),lat(0), lon(0){}

node::node(node && mnode):id(std::move(mnode.id)), lat(mnode.lat),
  lon(mnode.lon){
  mnode.id.clear();
}

node::node(node & cnode):id(cnode.id), lat(cnode.lat), lon(cnode.lon){}

void node::print(){
  cout << "Node " << id << " lat:" << lat << " lon:" << lon << '\n';
}

void check_highway(string & type){
  if(!type.compare("motorway") || !type.compare("primary")){
    return ;
  }
  else if(!type.compare("residential") || !type.compare("secondary")){
    return ;
  }
  else if(!type.compare("service") || !type.compare("tertiary")){
    return ;
  }
  else if(!type.compare("trunk") || !type.compare("unclassified")){
    return ;
  }
  type.clear();
}

bool parse_xml(string data_s, string out_s){
  ifstream data(data_s);
  ofstream out(out_s);
  vector<node> nodes;
  vector<string> nds;
  node t_node;
  string temp{}, type{}, id{};
  int counter{0};
  size_t max = std::numeric_limits<streamsize>::max();
  //ignore the first 3 lines of the xml file
  data.ignore(max, '\n');
  data.ignore(max, '\n');
  data.ignore(max, '\n');
  //start reading nodes;
  while(true){
    data >> temp;
    //cout << "Read " << temp << endl;
    //if it's not a node tag break
    if(!temp.compare("<node")){
      data >> temp;
      //copy the id
      t_node.id = std::move(temp.substr(4, temp.length()-5));
      //parse latitude
      data >> temp;
      t_node.lat = stod(temp.substr(5));
      //parse longitute
      data >> temp;
      t_node.lon = stod(temp.substr(5));
      //move node to the vector
      nodes.push_back(std::move(t_node));
      //cout << "Node read" << endl;
      counter++;
    }
    else if(!temp.compare("<way")){
      break;
    }
    //ignore the rest of the line
    data.ignore(max, '\n');
  }

  /*for(int i=0; i<nodes.size(); i++)
    nodes[i].print();
  cout << std::flush;*/

  while(true){
    if(!temp.compare("<way")){
      data >> temp;
      id = temp.substr(4, temp.length()-5);
    }
    else if(!temp.compare("<nd")){
      data >> temp;
      nds.push_back(std::move(temp.substr(5, temp.length()-8)));
    }
    else if(!temp.compare("<tag")){
      data >> temp;
      if(!temp.compare("k=\"highway\"")){
        data >> temp;
        type = temp.substr(3, temp.length()-6);
        //cout << "Type is " << type <<'\n';
        //check if it's a highway we're interested in
        check_highway(type);
      }
    }
    else if(!temp.compare("</way>")){
      //write road to file if valid
      if(!type.empty()){
        out << id << ' ' << type << ' ' << '\n';
      }
      id.clear();
      type.clear();
      nds.clear();
    }
    else if(!temp.compare("<relation")){
      cout << "Will break" << endl;
      //relation tags are in the end of the file so we're done
      break;
    }
    data.ignore(max, '\n');
    data >> temp;
  }
  cout << "Nodes read: " << counter << endl;
  return true;
}
