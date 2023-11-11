cmake_minimum_required(VERSION 3.10)

project(HelloWorld)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
find_package(fmt CONFIG REQUIRED)
find_package(unofficial-avro-cpp CONFIG REQUIRED)


add_executable(HelloWorld cpx.hh manifest-list.hh main.cpp)

target_compile_features(HelloWorld PRIVATE cxx_std_17)

target_link_libraries(HelloWorld PRIVATE unofficial::avro-cpp::avrocpp)

target_link_libraries(HelloWorld PRIVATE fmt::fmt)
