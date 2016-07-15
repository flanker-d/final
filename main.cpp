#include "args_parser.h"

int main(int argc, char *argv[])
{
  args_parser parser;
  server_params_t params = parser.parse_arguments(argc, argv);
  return 0;
}
