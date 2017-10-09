#ifndef DATA_OPS_H
#define DATA_OPS_H

int parse_arguments(int argc, char ** argv, std::string &data_s,
  std::string &query_s, int &k, int &L, std::string &out_s, bool &stats,
  std::string &func, std::string &hash);
#endif
