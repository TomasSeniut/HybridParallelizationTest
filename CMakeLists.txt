cmake_minimum_required(VERSION 3.7.2)
project(HybridParallelization C)


find_package(MPI REQUIRED)

set(CMAKE_C_FLAGS "-fopenmp")

set(CMAKE_C_STANDARD 99)

include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

set(SOURCE_FILES main.c)

add_executable(HybridParallelization main.c simpleTest.c test.h jobShare.c notifyProcesses.c queue.c queue.h testQueue.c IO.c IO.h)

