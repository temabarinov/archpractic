cmake_minimum_required(VERSION 3.16)

project(myproject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Wt REQUIRED COMPONENTS wt wtdbo)
find_package(Catch2 REQUIRED)
find_package(libpqxx REQUIRED)

add_executable(thread1 thread/thread1.cpp)
add_executable(thread2 thread/thread2.cpp)

add_executable(psql1 wt/psql1.cpp)

target_link_libraries(psql1 PRIVATE libpqxx::pqxx)





