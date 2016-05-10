# cmake_minimum_required(VERSION <specify CMake version here>)
project(Producer_Consumer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES Common.h Data.h Data.cpp Receiver.h Receiver.cpp Sender.h Sender.cpp main.h main.cpp main.h)
add_executable(Producer_Consumer ${SOURCE_FILES})