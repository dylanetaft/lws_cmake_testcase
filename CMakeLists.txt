cmake_minimum_required(VERSION 3.12)
project(wallet)
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)

add_compile_definitions(LWS_IPV6=1 LWS_LOGGING_BITFIELD_SET=LLL_ERR|LLL_WARN|LLL_DEBUG|LLL_USER|LLL_NOTICE|LLL_INFO|LLL_DEBUG|LLL_PARSER|LLL_HEADER)
add_subdirectory(extern_libs/libwebsockets)
add_executable(test testcase.c)
target_link_libraries(test extern_libs/libwebsockets)

