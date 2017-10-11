#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

//data_ops contains all the functions for the intialization of the problem
//e.g. parsing command line arguments, getting input from the user,
//getting input from the files etc.

int parse_arguments(int argc, char ** argv, std::string &data_s,
  std::string &query_s, int &k, int &L, std::string &out_s, bool &stats,
  std::string &func, std::string &hash){

  //we start from 1 to skip the name of the program
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
      func = argv[++i];
    else if(!strcmp(argv[i],"-hash"))
      hash = argv[++i];
    else
      cerr << "Wrong paramater given, it will be ignored" << endl;
    //advance to the next parameter
    //if parameter required 2 arguments, one incremention is already done
      i++;
    }
  return 1;
}

void input_parameters(std::string &data_s, std::string &func, std::string &hash){
  int choice{};

  if(data_s.empty()){
    cout << "Give the path to the dataset file: " << endl;
    cin >> data_s;
  }

  if(func.empty()){
    cout << "Specify the distance function: " << endl;
    cout << "1. DFT - Discrete Frechet Traversal." << endl;
    cout << "2. DTW - Dynamic Time Warping." << endl;
    //user gives a number and then we use the conditional operator
    cin >> choice;
    func = choice-1 ? "DTW" : "DFT";
  }

  if(hash.empty()){
    cout << "Specify the hash: " << endl;
    cout << "1. Classic." << endl;
    cout << "2. Probabilistic (LSH)." << endl;
    cin >> choice;
    hash = choice-1 ? "probabilistic" : "classic";
  }
}

int read_dataset_curves(std::string const data_s, std::vector<curve> & curves){
  ifstream data("data_s");

  if (!data.is_open()){
    //test if there is a file to get the data from
    cout << "couldn't find data file!" << endl;
    return -1;
  }

  data.close();
}
