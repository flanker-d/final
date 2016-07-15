#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <cstdint>
#include <iostream>
#include <cstdio>
#include <cinttypes>

#define MAX_EVENTS 4096

typedef struct server_params_t
{
  std::string host;
  std::uint16_t port;
  std::string directory;
  server_params_t() : host("0.0.0.0"), port(12345), directory("/home") {}

} server_params_t;

#endif // DATA_TYPES_H
