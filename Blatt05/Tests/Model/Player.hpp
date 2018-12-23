#ifndef TEST_PLAYER_HPP
#define TEST_PLAYER_HPP

#include "../../Model/Player.hpp"

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

TEST(Player, Scale) {
    model::Player player{{0,0},{1,1},{0,0}};
    EXPECT_DOUBLE_EQ((player.getPosition() - model::Vec{0,0}).norm(), 0);
    EXPECT_DOUBLE_EQ((player.getSize() - model::Vec{1,1}).norm(), 0);
    player.scaleSize(2);
    EXPECT_DOUBLE_EQ((player.getPosition() - model::Vec{0,0}).norm(), 0);
    EXPECT_DOUBLE_EQ((player.getSize() - model::Vec{2,2}).norm(), 0);
    player.scaleSize(2);
    EXPECT_DOUBLE_EQ((player.getPosition() - model::Vec{0,0}).norm(), 0);
    EXPECT_DOUBLE_EQ((player.getSize() - model::Vec{2,2}).norm(), 0);
    player.resetScale();
    EXPECT_DOUBLE_EQ((player.getPosition() - model::Vec{0,0}).norm(), 0);
    EXPECT_DOUBLE_EQ((player.getSize() - model::Vec{1,1}).norm(), 0);
}

TEST(Player, ScaleFail) {
    model::Player player{{0,0},{0,0},{0,0}};
    EXPECT_DEATH(player.scaleSize(-1.0), "");
    EXPECT_DEATH(player.scaleSize(0.0), "");
    EXPECT_NO_FATAL_FAILURE(player.scaleSize(2.0));
}

#endif //TEST_PLAYER_HPP
