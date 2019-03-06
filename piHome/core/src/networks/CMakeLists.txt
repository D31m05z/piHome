cmake_minimum_required(VERSION 3.12)
project(networking)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server PRIVATE piHome)
target_compile_definitions(server PRIVATE -DBUILD_SERVER_APP)
