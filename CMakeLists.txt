cmake_minimum_required(VERSION 3.13)
project(Virtual_File_System)

set(CMAKE_CXX_STANDARD 14)

add_executable(Virtual_File_System main.cpp Directory.cpp Directory.h File.cpp File.h virtualFileSystem.cpp virtualFileSystem.h freeSpaceManager.cpp freeSpaceManager.h blocksAllocation.cpp blocksAllocation.h contiguousAllocation.cpp contiguousAllocation.h linkedAllocation.cpp linkedAllocation.h indexedAllocation.cpp indexedAllocation.h Block.cpp Block.h)