cmake_minimum_required(VERSION 3.12)
project(ndnfs_client)

set(CMAKE_CXX_STANDARD 14)

add_executable(ndnfs_client ndnfs-client.cpp ndnfs-client.h connect.h connect.cpp)

include_directories(/usr/include)
link_directories(/usr/lib)

target_link_libraries(ndnfs_client jsoncpp)