cmake_minimum_required(VERSION 2.8)
set(PROJECT final)
project(${PROJECT})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++11 -pthread")
set(SOURCES_FILES
    main.cpp
    args_parser.cpp
    http_server.cpp
    client_session.cpp
    http_parser.cpp
    daemonize.cpp
    sessions_vector.cpp)
set(HEADERS_FILES
    data_types.h
    args_parser.h
    http_server.h
    client_session.h
    http_parser.h
    daemonize.h
    sessions_vector.h)
add_executable(${PROJECT_NAME} ${SOURCES_FILES} ${HEADERS_FILES})
