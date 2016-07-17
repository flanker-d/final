#include "args_parser.h"
#include "http_server.h"
//#include "daemonize.h"
#include <unistd.h>

//#define LOCALE_DEBUG 1

int main(int argc, char *argv[])
{
#ifdef LOCALE_DEBUG
  std::unique_ptr<args_parser> parser(new args_parser);
  server_params_t params = parser->get_params();
#else
  //std::unique_ptr<daemonize> daem(new daemonize);
  daemon(0, 0);
  std::unique_ptr<args_parser> parser(new args_parser);
  server_params_t params = parser->parse_arguments(argc, argv);
#endif
  std::unique_ptr<http_server> server(new http_server(params));
  return 0;
}
