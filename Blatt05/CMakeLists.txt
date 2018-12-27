cmake_minimum_required(VERSION 3.0)
project(FlappyWizard)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif ()

set(SOURCE_FILES Model/GameItem.cpp Model/Player.cpp Model/Obstacle.cpp
        Model/DoublePoints.cpp Model/Invulnerable.cpp Model/Troll.cpp Model/TurboMode.cpp
        Model/HighscoreSaver.cpp
        Controller/Environment.cpp Controller/Config.cpp
        Controller/ResourceConfig.cpp Controller/GameConfig.cpp
        View/Screen.cpp View/StartScreen.cpp View/HelpScreen.cpp View/GameScreen.cpp
        View/GameOverScreen.cpp View/HighscoreScreen.cpp View/ExitScreen.cpp
        View/Button.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} stdc++fs sfml-graphics sfml-window sfml-system)

# Tests
project(Test)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})


add_executable(${PROJECT_NAME} Tests/main.cpp ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBS} stdc++fs gtest pthread sfml-graphics sfml-window sfml-system)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

