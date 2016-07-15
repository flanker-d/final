#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include "data_types.h"
#include <vector>
#include <regex>

class http_parser
{
public:
  http_parser(server_params_t &params) : params_(params)
  {
  }
  request_params_t parse_http_request(std::string &request)
  {
    std::regex re_file("GET (.+)?(\\?)(.+) HTTP");
    std::smatch match_file;
    if(std::regex_search(request, match_file, re_file))
    {
      std::cout << "Match: " << match_file[1] << std::endl;
      request_params_.file = match_file[1];
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

  std::string get_response()
  {
    std::string full_path(params_.directory);
    full_path += request_params_.file;

    FILE *file_ptr = fopen(full_path.c_str(), "r");
    if(file_ptr == nullptr)
    {
      response_.append("HTTP/1.0 404 Not Found\r\n");
      response_.append("Content-Type: text/html\r\n\r\n");
      response_.append("<html><head><title>404</title></head>");
      response_.append("<body>404 Not Found</body></html>\r\n");
    }

    return response_;
  }

private:
  server_params_t &params_;
  request_params_t request_params_;
  std::string response_;
};

#endif // HTTP_PARSER_H
