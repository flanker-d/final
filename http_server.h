#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "data_types.h"
#include "client_session.h"
#include <mutex>

#include <fcntl.h>

class http_server
{
private:
  int set_nonblock(int fd);
  void set_reusable(int sock);

public:
  http_server(server_params_t &params);

private:
  server_params_t server_params_;
  int master_socket_;
};

#endif // HTTP_SERVER_H
