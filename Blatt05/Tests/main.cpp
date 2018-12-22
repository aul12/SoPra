#include "gtest/gtest.h"

#include "Vector.h"
#include "Rectangle.hpp"
#include "GameItem.hpp"
#include "Player.hpp"
#include "Obstacle.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

