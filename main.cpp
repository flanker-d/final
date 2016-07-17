#include "args_parser.h"
#include "http_server.h"
#include "daemonize.h"

int main(int argc, char *argv[])
{
  daemonize daem;
  args_parser parser;
  server_params_t params = parser.parse_arguments(argc, argv);
  //server_params_t params = parser.get_params();
  http_server server(params);
  return 0;
}
