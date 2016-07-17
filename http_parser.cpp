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
  std::regex re_file("GET (\\/)?([\\w.\\/]+)?([\\?])?(.+)? HTTP");
  std::smatch match_file;
  if(std::regex_search(request, match_file, re_file))
  {
    std::cout << "Match: " << match_file[2] << std::endl;
    request_params_.file = match_file[2];
  }

  std::regex re_mime("Accept: (.+\\/\\w+)?(,)");
  std::smatch match_mime;
  if(std::regex_search(request, match_mime, re_mime))
  {
    std::cout << "Match: " << match_mime[1] << std::endl;
    request_params_.mime_type = match_mime[1];
  }
  return request_params_;
}

std::string http_parser::get_response()
{
  std::string full_path(params_.directory);
  full_path += request_params_.file;

  std::ifstream read_input(full_path);
  if(read_input.is_open())
  {
    int size = get_file_size(read_input);
    std::unique_ptr<char> input_file(new char[size]);
    bzero(input_file.get(), size);
    read_input.read(input_file.get(), size);
    read_input.close();

    response_.append("HTTP/1.0 200 OK\r\n");
    response_.append("Connection: close\r\n");
    response_.append("Content-Type: text/html\r\n\r\n");
    response_.append(input_file.get());
  }
  else
  {
    response_.append("HTTP/1.0 404 Not Found\r\n");
    response_.append("Content-Type: text/html\r\n\r\n");
    response_.append("<html><head><title>404</title></head>");
    response_.append("<body>404 Not Found</body></html>\r\n");
  }

  return response_;
}
