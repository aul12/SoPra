#ifndef TEST_OBSTACLE_HPP
#define TEST_OBSTACLE_HPP

#include "../../Model/Obstacle.hpp"

TEST(Obstacle, HeightScale) {
    model::Obstacle obstacleTop{{0,0.5},{1,1}, model::ObstacleSide::TOP};
    model::Obstacle obstacleBot{{0,9.5},{1,1}, model::ObstacleSide::BOTTOM};
    EXPECT_DOUBLE_EQ(obstacleTop.getHeightScale(), 1);
    EXPECT_DOUBLE_EQ(obstacleBot.getHeightScale(), 1);
    obstacleTop.setHeightScale(2.0);
    obstacleBot.setHeightScale(2.0);
    EXPECT_DOUBLE_EQ((obstacleTop.getPosition()-model::Vec{0,1}).norm(), 0);
    EXPECT_DOUBLE_EQ((obstacleBot.getPosition()-model::Vec{0,9}).norm(), 0);
    EXPECT_DOUBLE_EQ((obstacleTop.getSize()-model::Vec{1,2}).norm(), 0);
    EXPECT_DOUBLE_EQ((obstacleBot.getSize()-model::Vec{1,2}).norm(), 0);
    obstacleBot.resetScale();
    obstacleTop.resetScale();
    EXPECT_DOUBLE_EQ((obstacleTop.getPosition()-model::Vec{0,0.5}).norm(), 0);
    EXPECT_DOUBLE_EQ((obstacleBot.getPosition()-model::Vec{0,9.5}).norm(), 0);
    EXPECT_DOUBLE_EQ((obstacleTop.getSize()-model::Vec{1,1}).norm(), 0);
    EXPECT_DOUBLE_EQ((obstacleBot.getSize()-model::Vec{1,1}).norm(), 0);
}

TEST(Obstacle, HeightScaleFail) {
    model::Obstacle obstacle{{0,0.5},{1,1}, model::ObstacleSide::TOP};
    EXPECT_DEATH(obstacle.setHeightScale(0.0), "");
    EXPECT_DEATH(obstacle.setHeightScale(-1.0), "");
    EXPECT_NO_FATAL_FAILURE(obstacle.setHeightScale(2.0));
}

#endif //TEST_OBSTACLE_HPP
