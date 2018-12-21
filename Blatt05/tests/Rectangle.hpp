#ifndef TEST_RECTANGLE_HPP
#define TEST_RECTANGLE_HPP

#include "../Util/Rectangle.hpp"

TEST(Rectangle, contains) {
    EXPECT_TRUE((Rectangle<int>{{0,0},{1,1}}.contains(Vector<2,int>{0,0})));
    EXPECT_TRUE((Rectangle<int>{{1,1},{2,2}}.contains(Vector<2,int>{1,2})));
    EXPECT_TRUE((Rectangle<int>{{0,0},{1,1}}.contains(Vector<2,int>{1,1})));
    EXPECT_TRUE((Rectangle<int>{{0,0},{1,1}}.contains(Vector<2,int>{1,0})));
    EXPECT_FALSE((Rectangle<int>{{0,0},{1,1}}.contains(Vector<2,int>{0,-1})));
    EXPECT_FALSE((Rectangle<int>{{1,1},{2,2}}.contains(Vector<2,int>{1,4})));
    EXPECT_FALSE((Rectangle<int>{{0,0},{1,1}}.contains(Vector<2,int>{1,2})));
    EXPECT_FALSE((Rectangle<int>{{0,0},{1,1}}.contains(Vector<2,int>{1,-1})));
}

TEST(Rectangle, constructor) {
    EXPECT_DEATH((Rectangle<int>{{0,0},{-1,0}}), "");
    EXPECT_DEATH((Rectangle<int>{{0,0},{-1,-1}}), "");
    EXPECT_DEATH((Rectangle<int>{{0,0},{0,-1}}), "");
    EXPECT_DEATH((Rectangle<int>{{0,0},{-100,0}}), "");
    EXPECT_NO_FATAL_FAILURE((Rectangle<int>{{0,0},{100,0}}));
    EXPECT_NO_FATAL_FAILURE((Rectangle<int>{{0,0},{0,0}}));
    EXPECT_NO_FATAL_FAILURE((Rectangle<int>{{0,0},{100,100}}));
    EXPECT_NO_FATAL_FAILURE((Rectangle<int>{{0,0},{0,100}}));
}

#endif //TEST_RECTANGLE_HPP
