#include "http_parser.h"

int http_parser::get_file_size(std::ifstream &read_input)
{
  int begin = read_input.tellg();
  read_input.seekg (0, std::ios::end);
  int end = read_input.tellg();
  int size = end - begin;
  read_input.seekg (0, std::ios::beg);

  return size;
}

http_parser::http_parser(server_params_t &params) : params_(params)
{
}

request_params_t http_parser::parse_http_request(std::string &request)
{
  int pos_end = request.find(" HTTP", 0);
  if(pos_end != std::string::npos)
  {
    std::string cut_request = request.substr(4, pos_end - 4);
    int params_begin = cut_request.find('?', 0);
    if(params_begin != std::string::npos)
    {
      std::string cut_req_without_params = cut_request.substr(0, params_begin);
      request_params_.file = cut_req_without_params;
    }
    else
      request_params_.file = cut_request;
  }
  return request_params_;
}

std::string http_parser::get_response()
{
  std::string full_path(params_.directory);
  full_path += request_params_.file;

  //std::cout << "full path: " << full_path << std::endl;

  std::ifstream read_input(full_path);
  if(read_input.is_open())
  {
    int size = get_file_size(read_input);
    std::unique_ptr<char> input_file(new char[size]);
    bzero(input_file.get(), size);
    read_input.read(input_file.get(), size);
    read_input.close();

    response_.append("HTTP/1.0 200 OK\r\n");
    response_.append("Content-Type: text/html\r\n");
    response_.append("Content-length:" + std::to_string(size) +"\r\n");
    response_.append("Connection: close\r\n\r\n");
    response_.append(input_file.get());
  }
  else
  {
    //std::string page404("<html><head><title>404</title></head><body>404 Not Found</body></html>\r\n");
    response_.append("HTTP/1.0 404 Not Found\r\n");
    response_.append("Content-length: 0\r\n");
    response_.append("Content-Type: text/html\r\n\r\n");
    // + std::to_string(page404.size()) +"\r\n");
    //response_.append("Connection: close\r\n\r\n");
    //response_.append(page404);
  }

  return response_;
}
