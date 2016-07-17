#include "args_parser.h"

args_parser::args_parser()
{

}

server_params_t args_parser::parse_arguments(int argc, char *argv[])
{
  int option = 0;

  while( (option = getopt(argc, argv, "h:p:d:")) != -1)
  {
    switch(option)
    {
    case 'h':
      server_params_.host = optarg;
      break;
    case 'p':
      server_params_.port = atoi(optarg);
      break;
    case 'd':
      server_params_.directory = optarg;
      break;
    default:
      break;
    }
  }

  return server_params_;
}

void args_parser::print_args()
{
  //std::cout << "ip: " << server_params_.host << " port: " << server_params_.port << " dir: " <<server_params_.directory << std::endl;
}

const server_params_t &args_parser::get_params() const
{
  return server_params_;
}
