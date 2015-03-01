cmake_minimum_required(VERSION 2.8.4)
project(Doppler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Doppler main.cpp)
add_executable(fft frequency-domain-filtering.cpp)
add_executable(wav-test wav-test.cpp)

target_link_libraries(Doppler Aquila ooura_fft sfml-system sfml-audio)
target_link_libraries(fft Aquila ooura_fft)
target_link_libraries(wav-test Aquila ooura_fft sfml-system sfml-audio)