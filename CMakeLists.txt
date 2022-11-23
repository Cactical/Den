cmake_minimum_required(VERSION 3.16)
project(DEN VERSION 0.1.0 LANGUAGES CXX)
add_subdirectory(devenv.proj)
add_executable(devenv devenv.proj/src/devenv.cpp)
target_include_directories(devenv PRIVATE devenv.proj/inc)

include(CTest)
enable_testing()

install(TARGETS devenv RUNTIME DESTINATION bin)
set(CMAKE_CXX_STANDARD 17)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

