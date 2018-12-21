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

TEST(Rectangle, intersects) {
    Rectangle<int> r1{{0,0}, {3,3}};
    Rectangle<int> r2{{1,1}, {1,1}};
    Rectangle<int> r3{{-1,1}, {5,4}};
    Rectangle<int> r4{{-10,-10,},{1,1}};
    EXPECT_TRUE(r1.intersects(r2));
    EXPECT_TRUE(r2.intersects(r1));
    EXPECT_TRUE(r3.intersects(r1));
    EXPECT_TRUE(r1.intersects(r3));
    EXPECT_TRUE(r2.intersects(r3));
    EXPECT_TRUE(r3.intersects(r2));
    EXPECT_FALSE(r1.intersects(r4));
    EXPECT_FALSE(r4.intersects(r1));
    EXPECT_FALSE(r2.intersects(r4));
    EXPECT_FALSE(r4.intersects(r2));
    EXPECT_FALSE(r3.intersects(r4));
    EXPECT_FALSE(r4.intersects(r3));
}

TEST(Rectangle, shift) {
    EXPECT_EQ((Rectangle<int>{{0,0},{1,1}} + Vector<2,int>{{2,3}}), (Rectangle<int>{{2,3},{1,1}}));
    EXPECT_EQ((Rectangle<int>{{4,17},{1,4}} + Vector<2,int>{{-4,-34}}), (Rectangle<int>{{0,-17},{1,4}}));
}

TEST(Rectangle, equal) {
    Rectangle<int> r1{{0,0},{1,1}};
    Rectangle<int> r2{{0,0},{1,1}};
    Rectangle<int> r3{{0,0},{1,2}};
    EXPECT_TRUE(r1 == r2);
    EXPECT_TRUE(r2 == r1);
    EXPECT_FALSE(r1 == r3);
    EXPECT_FALSE(r3 == r1);
    EXPECT_FALSE(r2 == r3);
    EXPECT_FALSE(r3 == r2);
}

TEST(Rectangle, getSize) {
    Vector<2,int> s1{{10,10}};
    Vector<2,int> s2{{1,10}};
    Vector<2,int> s3{{10,100}};
    Vector<2,int> s4{{19,17}};

    EXPECT_EQ((Rectangle<int>{{0,0}, s1}.getSize()), s1);
    EXPECT_EQ((Rectangle<int>{{0,0}, s2}.getSize()), s2);
    EXPECT_EQ((Rectangle<int>{{0,0}, s3}.getSize()), s3);
    EXPECT_EQ((Rectangle<int>{{0,0}, s4}.getSize()), s4);
}

#endif //TEST_RECTANGLE_HPP
