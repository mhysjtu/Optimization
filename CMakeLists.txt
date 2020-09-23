cmake_minimum_required( VERSION 2.8 )
project(optimization)

find_package(Ceres REQUIRED)

include_directories(${CERES_INCLUDE_DIRS})

add_executable(hello_ceres src/helloworld.cpp)
target_link_libraries(hello_ceres ${CERES_LIBRARIES})