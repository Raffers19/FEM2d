cmake_minimum_required(VERSION 3.20)

project(FEMSyst LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OpenMP
find_package(OpenMP REQUIRED)

# Eigen
include(FetchContent)

set(BUILD_TESTING OFF CACHE BOOL
    "Disable dependency tests" FORCE)

set(EIGEN_BUILD_TESTING OFF CACHE BOOL
    "Disable Eigen tests" FORCE)

set(EIGEN_BUILD_DOC OFF CACHE BOOL
    "Disable Eigen documentation" FORCE)

FetchContent_Declare(
    eigen
    URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(eigen)

# Testing
enable_testing()

# Project directories
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)