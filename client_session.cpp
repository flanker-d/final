#include "client_session.h"

void client_session::client_response(int sock)
{
  //std::cout << "response " << sock << std::endl;
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
    send(sock, buffer, rd, MSG_NOSIGNAL);
    std::cout << buffer << std::endl << "------------------------------------" << std::endl;
  }
  else
  {
    //std::cout << "error " << rd << std::endl;
  }
  shutdown(sock_, SHUT_RDWR);
  close(sock_);
}

client_session::client_session(int sock) :
  sock_(sock),
  session_(&client_session::client_response, this, sock)
{
  std::cout << "client connected" << std::endl;
}

client_session::~client_session()
{
  session_.join();
  std::cout << "client disconnected" << std::endl;
}
