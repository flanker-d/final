#include "args_parser.h"
#include "http_server.h"
#include "daemonize.h"

int main(int argc, char *argv[])
{
  std::unique_ptr<daemonize> daem(new daemonize);
  std::unique_ptr<args_parser> parser(new args_parser);
  server_params_t params = parser->parse_arguments(argc, argv);
  //server_params_t params = parser->get_params();
  std::unique_ptr<http_server> server(new http_server(params));
  return 0;
}
