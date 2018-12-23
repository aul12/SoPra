#ifndef TEST_ENVIRONMENT_HPP
#define TEST_ENVIRONMENT_HPP

#include "../../Controller/Environment.hpp"

TEST(Environment, Constructor) {
    EXPECT_NO_THROW(controller::Environment{"../config.json"});
}

TEST(Environment, SingleUpdate) {
    controller::Environment environment{"../config.json"};
    EXPECT_EQ(environment.update(1), controller::UpdateResult::UPDATED);
}

TEST(Environment, ContinousUpdate) {
    controller::Environment environment{"../config.json"};
    for (int c=0; c<1000; c++) {
        EXPECT_NO_FATAL_FAILURE(environment.update(1));
    }
}

TEST(Environment, PlayerUp) {
    controller::Environment environment{"../config.json"};
    EXPECT_NO_FATAL_FAILURE(environment.playerUp(1));
    EXPECT_DEATH(environment.playerUp(0), "");
    EXPECT_DEATH(environment.playerUp(-1), "");
}

TEST(Environment, UpdateFail) {
    controller::Environment environment{"../config.json"};
    EXPECT_DEATH(environment.update(-1), "");
    EXPECT_DEATH(environment.update(0), "");
    EXPECT_NO_FATAL_FAILURE(environment.update(1));
}

#endif //TEST_ENVIRONMENT_HPP
