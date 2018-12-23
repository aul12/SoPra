#ifndef TEST_ITEM_HPP
#define TEST_ITEM_HPP

/*
 * Because Item is abstract we can't test it directly, that's why we test it indirectly via one of it's children namely
 * DoublePoints
 */

#include "../../Model/DoublePoints.hpp"

TEST(Item, GetRemainingTime) {
    EXPECT_DOUBLE_EQ((model::DoublePoints{{0,0},{0,0},10}.getRemainingTime()), 10);
    EXPECT_DOUBLE_EQ((model::DoublePoints{{0,0},{0,0},0}.getRemainingTime()), 0);
    EXPECT_DOUBLE_EQ((model::DoublePoints{{0,0},{0,0},100}.getRemainingTime()), 100);
    EXPECT_DOUBLE_EQ((model::DoublePoints{{0,0},{0,0},17}.getRemainingTime()), 17);
}

TEST(Item, DecreaseRemainingTime) {
    model::DoublePoints item{{0,0},{0,0},100};
    EXPECT_DOUBLE_EQ(item.getRemainingTime(), 100);
    item.decreaseRemainingTimeBy(25);
    EXPECT_DOUBLE_EQ(item.getRemainingTime(), 75);
    item.decreaseRemainingTimeBy(50);
    EXPECT_DOUBLE_EQ(item.getRemainingTime(), 25);
    item.decreaseRemainingTimeBy(40);
    EXPECT_DOUBLE_EQ(item.getRemainingTime(), -15);
}

#endif //TEST_ITEM_HPP
