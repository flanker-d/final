#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include "data_types.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <thread>

#define BUFFER_SIZE 1024

class client_session
{
public:
  void client_response(int sock);

public:
  client_session(int sock);
  ~client_session();
private:
  int sock_;
  std::thread session_;
};

#endif // CLIENT_SESSION_H
