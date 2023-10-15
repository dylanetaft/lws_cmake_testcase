cmake_minimum_required(VERSION 3.12)
project(tc)
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)
OPTION (LWS_WITH_MINIMAL_EXAMPLES OFF)
option(LWS_IPV6 ON)
add_subdirectory(extern_libs/libwebsockets)

add_executable(test testcase.c)
target_link_libraries(test websockets)
target_include_directories(test PRIVATE LIBWEBSOCKETS_INCLUDE_DIRS)

