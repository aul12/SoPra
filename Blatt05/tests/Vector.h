#include "../Util/Vector.h"

TEST(VectorTest, VectorAddVector) {
    EXPECT_EQ((Vector<1,int>({{1}}) + Vector<1,int>({{2}})), (Vector<1,int>({{3}})));
}
