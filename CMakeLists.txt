cmake_minimum_required( VERSION 2.8 )
project(optimization)

find_package(Ceres REQUIRED)

include_directories(${CERES_INCLUDE_DIRS})

add_executable(hello_ceres src/helloworld.cpp)
target_link_libraries(hello_ceres ${CERES_LIBRARIES})

add_executable(hello_ceres_numeric src/helloworld_numeric.cpp)
target_link_libraries(hello_ceres_numeric ${CERES_LIBRARIES})

add_executable(hello_ceres_analytic src/helloworld_analytic.cpp)
target_link_libraries(hello_ceres_analytic ${CERES_LIBRARIES})