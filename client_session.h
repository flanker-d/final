#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include "data_types.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#include <thread>

#include "http_parser.h"
#include "sessions_vector.h"

class sessions_vector;

#define BUFFER_SIZE 1024

class client_session : public std::enable_shared_from_this<client_session>
{
private:
  void client_response();

public:
  client_session(int sock, server_params_t &params, sessions_vector &sess_vec);
  ~client_session();

private:
  int sock_;
  std::thread thread_session_;
  server_params_t &params_;
  sessions_vector &sess_vect_;
};

#endif // CLIENT_SESSION_H
