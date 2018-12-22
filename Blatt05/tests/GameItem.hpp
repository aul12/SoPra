#ifndef TEST_GAMEITEM_HPP
#define TEST_GAMEITEM_HPP

#include "../GameItem.hpp"

TEST(GameItem, Position) {
    model::GameItem gameItem1{{0,0},{1,1}};
    model::GameItem gameItem2{{0,0},{2,4}};
    model::GameItem gameItem3{{2,3},{1,1}};
    EXPECT_DOUBLE_EQ((gameItem1.getPosition() - util::Vector<2, double>{{0.5,0.5}}).norm(), 0);
    EXPECT_DOUBLE_EQ((gameItem2.getPosition() - util::Vector<2, double>{{1,2}}).norm(), 0);
    EXPECT_DOUBLE_EQ((gameItem3.getPosition() - util::Vector<2, double>{{2.5, 3.5}}).norm(), 0);
}

#endif //TEST_GAMEITEM_HPP
