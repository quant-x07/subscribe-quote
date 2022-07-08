cmake_minimum_required(VERSION 2.8.9)
project (tstClient)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(/home/netsec/root/usr/local/include)
link_directories(/home/netsec/root/usr/local/lib)

add_executable(tstClient main.cpp MqttPub.cpp TraceCompress.cpp)

target_link_libraries(tstClient mosquitto pthread)
# z
