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

  set_nonblock(master_socket_);
  set_reusable(master_socket_);

  listen(master_socket_, SOMAXCONN);

  int epoll_obj = epoll_create1(0);
  struct epoll_event epoll_event;
  epoll_event.data.fd = master_socket_;
  epoll_event.events = EPOLLIN;
  epoll_ctl(epoll_obj, EPOLL_CTL_ADD, master_socket_, &epoll_event);

  while(true)
  {
    struct epoll_event events_array[MAX_EVENTS];
    int N = epoll_wait(epoll_obj, events_array, MAX_EVENTS, -1);
    for(int i = 0; i < N; i++)
    {
      if(events_array[i].data.fd == master_socket_)
      {
        int slave_socket = accept(master_socket_, 0, 0);
        set_nonblock(slave_socket);
        std::unique_ptr<client_session> session(new client_session(slave_socket));
      }
    }
  }
}
