cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

project(netpanzer)
add_subdirectory(src/client)
add_subdirectory(src/server)
add_subdirectory(src/core)

target_include_directories(np_client PRIVATE src/core)
target_include_directories(np_server PRIVATE src/core)

target_link_libraries(np_client np_core)
target_link_libraries(np_server np_core)
