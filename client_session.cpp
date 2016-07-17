#include "client_session.h"

void client_session::client_response()
{
  std::cout << "begin response" << std::endl;
  std::unique_ptr<char> buffer(new char[BUFFER_SIZE]);
  bzero(buffer.get(), BUFFER_SIZE);
  int rd = recv(sock_, buffer.get(), BUFFER_SIZE, MSG_NOSIGNAL);
  if((rd == 0) && (errno != EAGAIN))
  {
    shutdown(sock_, SHUT_RDWR);
    close(sock_);
  }
  else if(rd > 0)
  {
    std::unique_ptr<http_parser> parser(new http_parser(params_));
    std::string request(buffer.get());
    parser->parse_http_request(request);
    std::string response = parser->get_response();

    send(sock_, response.c_str(), response.length(), MSG_NOSIGNAL);
  }
  else
  {
    //std::cout << "error " << rd << std::endl;
  }
  shutdown(sock_, SHUT_RDWR);
  close(sock_);
  std::cout << "end response" << std::endl;
}

client_session::client_session(int sock, server_params_t &params) :
  sock_(sock),
  thread_session_(&client_session::client_response, this),
  params_(params)
{
  std::cout << "client connected" << std::endl;
  //thread_session_.detach();
}

client_session::~client_session()
{
  std::cout << "try to join" << std::endl;
  thread_session_.join();
  std::cout << "client disconnected" << std::endl;
}
