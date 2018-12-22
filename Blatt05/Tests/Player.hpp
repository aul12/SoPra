#ifndef TEST_PLAYER_HPP
#define TEST_PLAYER_HPP

#include "../Model/Player.hpp"

TEST(Player, Accelerate) {
    model::Player player{{0,0},{0,0}};
    player.accelerate({1,1});
    EXPECT_DOUBLE_EQ((player.getSpeed()-model::Vec{1,1}).norm(), 0);
    player.accelerate({-1,1});
    EXPECT_DOUBLE_EQ((player.getSpeed()-model::Vec{0,2}).norm(), 0);
    player.accelerate({1,-4}, 0.5);
    EXPECT_DOUBLE_EQ((player.getSpeed()-model::Vec{0.5,0}).norm(), 0);
}

TEST(Player, Move) {
    model::Player player{{0,0},{0,0},{1,0}};
    player.move();
    EXPECT_DOUBLE_EQ((player.getPosition() - model::Vec{1,0}).norm(), 0);
    player.move(0.5);
    EXPECT_DOUBLE_EQ((player.getPosition() - model::Vec{1.5, 0}).norm(), 0);
}

#endif //TEST_PLAYER_HPP
