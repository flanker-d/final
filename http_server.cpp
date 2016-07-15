#include "http_server.h"

int http_server::set_nonblock(int fd)
{
  int flags;
#if defined(O_NONBLOCK)
  if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
    flags = 0;
  return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
  flags = 1;
  return ioctl(fd, FIOBIO, &flags);
#endif
}

void http_server::set_reusable(int sock)
{
  int optval = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

http_server::http_server(server_params_t &params) : server_params_(params)
{
  master_socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  struct sockaddr_in sock_addr;
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(server_params_.port);
  sock_addr.sin_addr.s_addr = inet_addr(server_params_.host.c_str());
  bind(master_socket_, (struct sockaddr *)(&sock_addr), sizeof(sock_addr));

  //set_nonblock(master_socket_);
  set_reusable(master_socket_);

  listen(master_socket_, SOMAXCONN);

  while(true)
  {
    int slave_socket = accept(master_socket_, 0, 0);
    if(slave_socket > 0)
    {
      std::shared_ptr<client_session> session(new client_session(slave_socket, server_params_));
      std::cout << "next iteration" << std::endl;
    }
  }
}
