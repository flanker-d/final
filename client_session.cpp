#include "client_session.h"

void client_session::client_response(int sock)
{
  char buffer[BUFFER_SIZE];
  bzero(buffer, BUFFER_SIZE);
  int rd = recv(sock, buffer, BUFFER_SIZE, MSG_NOSIGNAL);
  if((rd == 0) && (errno != EAGAIN))
  {
    shutdown(sock, SHUT_RDWR);
    close(sock);
  }
  else if(rd > 0)
  {
    http_parser parser(params_);
    std::string request(buffer);
    parser.parse_http_request(request);
    std::string response = parser.get_response();

    send(sock, response.c_str(), response.length(), MSG_NOSIGNAL);
  }
  else
  {
    //std::cout << "error " << rd << std::endl;
  }
  shutdown(sock_, SHUT_RDWR);
  close(sock_);
}

client_session::client_session(int sock, server_params_t &params) :
  sock_(sock),
  thread_session_(&client_session::client_response, this, sock),
  params_(params)
{
  std::cout << "client connected" << std::endl;
}

client_session::~client_session()
{
  thread_session_.join();
  std::cout << "client disconnected" << std::endl;
}
