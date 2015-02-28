cmake_minimum_required(VERSION 2.8.4)
project(Doppler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Doppler main.cpp)

target_link_libraries(Doppler Aquila ooura_fft sfml-system sfml-audio)