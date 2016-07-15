#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include "data_types.h"
#include <getopt.h>

class args_parser
{
public:
  args_parser();
  server_params_t parse_arguments(int argc, char *argv[]);
  void print_args();

private:
  server_params_t server_params_;
};

#endif // ARGS_PARSER_H
