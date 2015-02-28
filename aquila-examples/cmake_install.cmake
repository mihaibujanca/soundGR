# Install script for directory: /Users/ian/Development/aquila/aquila-src/examples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/ian/Development/aquila/aquila-build/examples/utility_functions/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/frame_iteration/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/wave_info/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/wave_iteration/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/window_plot/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/window_usage/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/text_plot/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/sine_generator/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/square_generator/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/triangle_generator/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/generators/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/am_modulation/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/fft_comparison/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/fft_simple_spectrum/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/fft_filter/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/spectrogram/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/mfcc_calculation/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/dtw_path_recovery/cmake_install.cmake")
  include("/Users/ian/Development/aquila/aquila-build/examples/sfml/cmake_install.cmake")

endif()

