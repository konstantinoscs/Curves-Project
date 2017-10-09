#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

int parse_arguments(int argc, char ** argv, std::string &data_s,
  std::string &query_s, int &k, int &L, std::string &out_s, bool &stats,
  std::string &func, std::string &hash){

  int i = 1;
  while(i<argc){
    if(!strcmp(argv[i],"-d"))
      data_s = argv[++i];
    else if(!strcmp(argv[i],"-q"))
      query_s = argv[++i];
    else if(!strcmp(argv[i],"-k"))
      k = atoi(argv[++i]);
    else if(!strcmp(argv[i],"-L"))
      L = atoi(argv[++i]);
    else if(!strcmp(argv[i],"-o"))
      out_s = argv[++i];
    else if(!strcmp(argv[i],"-stats"))
      stats = true;
    else if(!strcmp(argv[i],"-function"))
      func = atoi(argv[++i]);
    else if(!strcmp(argv[i],"-hash"))
      hash = atoi(argv[++i]);
    else
      cerr << "Wrong paramater given, it will be ignored" << endl;
    //advance to the next parameter
    //if parameter required 2 arguments, one incremention is already done
      i++;
    }
  return 1;
}
