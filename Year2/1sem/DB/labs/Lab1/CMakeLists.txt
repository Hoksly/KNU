cmake_minimum_required(VERSION 3.0.0)
project(Lab1 VERSION 0.1.0)

include(CTest)
enable_testing()





add_executable(Lab1 main.cpp lib/functions.hpp  lib/get.hpp lib/count.hpp lib/del.hpp lib/insert.hpp lib/update.hpp lib/get.cpp lib/functions.cpp lib/count.cpp lib/del.cpp lib/insert.cpp lib/update.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
