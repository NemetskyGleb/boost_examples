cmake_minimum_required(VERSION 3.5)

project(get_started LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BOOST_ROOT "C:/Program Files/boost/boost_1_76_0")

find_package(Boost 1.76.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(get_started main.cpp)
endif()


