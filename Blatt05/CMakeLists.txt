cmake_minimum_required(VERSION 3.0)
project(FlappyWizard)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES GameItem.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Tests
project(Test)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(${PROJECT_NAME} tests/main.cpp ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBS} -lgtest -lpthread)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

