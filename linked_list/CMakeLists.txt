cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(LLTest VERSION 1.0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(lltest_version.h.in lltest_version.h)
