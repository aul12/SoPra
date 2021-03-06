#ifndef TEST_VECTOR_HPP
#define TEST_VECTOR_HPP

#include "../../Util/Vector.hpp"

using namespace util;

TEST(Vector, AddVector) {
    EXPECT_EQ((Vector<1,int>{1} + Vector<1,int>{2}), (Vector<1,int>{3}));
    EXPECT_EQ((Vector<1,int>{-1} + Vector<1,int>{2}), (Vector<1,int>{1}));
    EXPECT_EQ((Vector<1,int>{17} + Vector<1,int>{38}), (Vector<1,int>{55}));
    EXPECT_EQ((Vector<1,int>{30} + Vector<1,int>{-18}), (Vector<1,int>{12}));
    EXPECT_EQ((Vector<2,int>{1, 10} + Vector<2,int>{2,3}), (Vector<2,int>{3,13}));
    EXPECT_EQ((Vector<2,int>{-1, 3} + Vector<2,int>{2,-3}), (Vector<2,int>{1,0}));
    EXPECT_EQ((Vector<2,int>{17, 4} + Vector<2,int>{38,-17}), (Vector<2,int>{55,-13}));
    EXPECT_EQ((Vector<2,int>{30, -17} + Vector<2,int>{-18, 34}), (Vector<2,int>{12,17}));
}

TEST(Vector, SubVector) {
    EXPECT_EQ((Vector<1,int>{1} - Vector<1,int>{2}), (Vector<1,int>{-1}));
    EXPECT_EQ((Vector<1,int>{-1} - Vector<1,int>{2}), (Vector<1,int>{-3}));
    EXPECT_EQ((Vector<1,int>{17} - Vector<1,int>{38}), (Vector<1,int>{-21}));
    EXPECT_EQ((Vector<1,int>{30} - Vector<1,int>{-18}), (Vector<1,int>{48}));
    EXPECT_EQ((Vector<2,int>{1, 10} - Vector<2,int>{2,3}), (Vector<2,int>{-1,7}));
    EXPECT_EQ((Vector<2,int>{-1, 3} - Vector<2,int>{2,-3}), (Vector<2,int>{-3,6}));
    EXPECT_EQ((Vector<2,int>{17, 4} - Vector<2,int>{38,-17}), (Vector<2,int>{-21,21}));
    EXPECT_EQ((Vector<2,int>{30, -17} - Vector<2,int>{-18, 34}), (Vector<2,int>{48,-17-34}));
}

TEST(Vector, DotProduct) {
    EXPECT_EQ((Vector<1,int>{1} * Vector<1,int>{2}), 2);
    EXPECT_EQ((Vector<1,int>{-1} * Vector<1,int>{2}), -2);
    EXPECT_EQ((Vector<1,int>{17} * Vector<1,int>{38}), 17*38);
    EXPECT_EQ((Vector<1,int>{30} * Vector<1,int>{-18}), -18*30);
    EXPECT_EQ((Vector<2,int>{1, 10} * Vector<2,int>{2,3}), 2+30);
    EXPECT_EQ((Vector<2,int>{-1, 3} * Vector<2,int>{2,-3}), -2-9);
    EXPECT_EQ((Vector<2,int>{17, 4} * Vector<2,int>{38,-17}), 17*38-4*17);
    EXPECT_EQ((Vector<2,int>{30, -17} * Vector<2,int>{-18, 34}), -30*18-17*34);
}

TEST(Vector, Scale) {
    EXPECT_EQ((Vector<1,int>{1} * 1), (Vector<1,int>{1}));
    EXPECT_EQ((Vector<1,int>{-1} * 2), (Vector<1,int>{-2}));
    EXPECT_EQ((Vector<1,int>{17} * 3), (Vector<1,int>{3*17}));
    EXPECT_EQ((Vector<1,int>{30} * -17), (Vector<1,int>{-30*17}));
    EXPECT_EQ((Vector<2,int>{1, 10} * 3), (Vector<2,int>{3, 30}));
    EXPECT_EQ((Vector<2,int>{-1, 3} * -4), (Vector<2,int>{4,-12}));
    EXPECT_EQ((Vector<2,int>{17, 4} * 2), (Vector<2,int>{34,8}));
    EXPECT_EQ((Vector<2,int>{30, -17} * -1), (Vector<2,int>{-30, 17}));
}

TEST(Vector, EqVector) {
    EXPECT_EQ((Vector<1,int>{1} == Vector<1,int>{2}), false);
    EXPECT_EQ((Vector<1,int>{1} == Vector<1,int>{1}), true);
    EXPECT_EQ((Vector<1,int>{-1} == Vector<1,int>{2}), false);
    EXPECT_EQ((Vector<1,int>{-1} == Vector<1,int>{-1}), true);
    EXPECT_EQ((Vector<1,int>{17} == Vector<1,int>{38}), false);
    EXPECT_EQ((Vector<1,int>{30} == Vector<1,int>{-18}), false);
    EXPECT_EQ((Vector<2,int>{1, 10} == Vector<2,int>{2,3}), false);
    EXPECT_EQ((Vector<2,int>{-1, 3} == Vector<2,int>{2,-3}), false);
    EXPECT_EQ((Vector<2,int>{17, 4} == Vector<2,int>{38,-17}), false);
    EXPECT_EQ((Vector<2,int>{30, -17} == Vector<2,int>{-18, 34}), false);
}

TEST(Vector, ConvertConstructor) {
    Vector<2, int> testi{1,2};
    Vector<2, double> testd{1,2};
    EXPECT_EQ((Vector<2, double>{testi}), testd);
}

TEST(Vector, InitializerListFail) {
    EXPECT_DEATH((Vector<1,int>{{1,2}}), "");
    EXPECT_DEATH((Vector<2,int>{1}), "");
    EXPECT_NO_FATAL_FAILURE((Vector<2,int>{{1,2}}));
}

TEST(Vector, GetSetBracketOp) {
    Vector<10, int> test{};
    for(int c=0; c<10; c++) {
        test.set(c, c*c);
        EXPECT_EQ(test.get(c), c*c);
        test[c] = c*c*c*17;
        EXPECT_EQ(test[c], c*c*c*17);
    }
}

TEST(Vector, Norm) {
    EXPECT_DOUBLE_EQ((Vector<1, int>{1}.norm()), (1));
    EXPECT_DOUBLE_EQ((Vector<1, int>{17}.norm()), (17));
    EXPECT_DOUBLE_EQ((Vector<2, int>{3,4}.norm()), (5));
    EXPECT_DOUBLE_EQ((Vector<2, int>{6,8}.norm()), (10));
    EXPECT_DOUBLE_EQ((Vector<3, int>{1,2,3}.norm()), (std::sqrt(14)));
}

#endif