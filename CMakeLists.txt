cmake_minimum_required(VERSION 3.16)
project(DEN VERSION 0.1.0 LANGUAGES CXX)
add_subdirectory(devenv)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

