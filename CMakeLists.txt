cmake_minimum_required(VERSION 2.8.3)
project(my_shared_ptr)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)
# add_library(${PROJECT_NAME} SHARED src/my_shared_ptr.cpp)

add_executable(tests tests/tests.cpp
    # tests/01-tests.cpp
    # tests/02-tests.cpp
    # tests/03-tests.cpp
    # tests/04-tests.cpp
    # tests/05-tests.cpp
    # tests/06-tests.cpp
    tests/07-tests.cpp
)


# target_link_libraries(tests ${PROJECT_NAME})
