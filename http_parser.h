#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include "data_types.h"
#include <vector>
#include <fstream>
#include <strings.h>
#include <memory>

class http_parser
{
private:
  int get_file_size(std::ifstream &read_input);

public:
  http_parser(server_params_t &params);
  request_params_t parse_http_request(std::string &request);
  std::string get_response();

private:
  server_params_t &params_;
  request_params_t request_params_;
  std::string response_;
};

#endif // HTTP_PARSER_H
