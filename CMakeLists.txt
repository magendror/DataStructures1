cmake_minimum_required(VERSION 3.0.0)
project(DataStructure1 VERSION 0.1.0)


#set(MTM_FLAGS_DEBUG "-std=c++11 -Wall  -Werror -pedantic-errors")
set(MTM_FLAGS_DEBUG "-std=c++11 -Wall")
set(MTM_FLAGS_RELEASE "{MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_CXX_FLAGS ${MTM_FLAGS_DEBUG})

add_executable(DataStructure1 main1.cpp function.cpp)