#ifndef TEST_ENVIRONMENT_HPP
#define TEST_ENVIRONMENT_HPP

#include "../../Controller/Environment.hpp"

TEST(Environment, Constructor) {
    EXPECT_NO_THROW(controller::Environment{"../config.json"});
}

TEST(Environment, Update) {
    controller::Environment environment{"../config.json"};
    EXPECT_EQ(environment.update(1), controller::UpdateResult::UPDATED);
}

TEST(Environment, UpdateFail) {
    controller::Environment environment{"../config.json"};
    EXPECT_DEATH(environment.update(-1), "");
    EXPECT_DEATH(environment.update(0), "");
    EXPECT_NO_FATAL_FAILURE(environment.update(1));
}

#endif //TEST_ENVIRONMENT_HPP
