#ifndef TEST_ENVIRONMENT_HPP
#define TEST_ENVIRONMENT_HPP

#include "../../Controller/Environment.hpp"

TEST(Environment, Constructor) {
    std::ifstream configStream{"../config.json"};
    nlohmann::json j;
    configStream >> j;
    EXPECT_NO_THROW(controller::Environment{j.get<controller::GameConfig>()});
}

TEST(Environment, SingleUpdate) {
    std::ifstream configStream{"../config.json"};
    nlohmann::json j;
    configStream >> j;
    controller::Environment environment{j.get<controller::GameConfig>()};
    EXPECT_EQ(environment.update(1), controller::UpdateResult::UPDATED);
}

TEST(Environment, ContinousUpdate) {
    std::ifstream configStream{"../config.json"};
    nlohmann::json j;
    configStream >> j;
    controller::Environment environment{j.get<controller::GameConfig>()};
    for (int c=0; c<1000; c++) {
        EXPECT_NO_FATAL_FAILURE(environment.update(1));
    }
}

TEST(Environment, PlayerUp) {
    std::ifstream configStream{"../config.json"};
    nlohmann::json j;
    configStream >> j;
    controller::Environment environment{j.get<controller::GameConfig>()};
    EXPECT_NO_FATAL_FAILURE(environment.playerUp(1));
    EXPECT_DEATH(environment.playerUp(0), "");
    EXPECT_DEATH(environment.playerUp(-1), "");
}

TEST(Environment, UpdateFail) {
    std::ifstream configStream{"../config.json"};
    nlohmann::json j;
    configStream >> j;
    controller::Environment environment{j.get<controller::GameConfig>()};
    EXPECT_DEATH(environment.update(-1), "");
    EXPECT_DEATH(environment.update(0), "");
    EXPECT_NO_FATAL_FAILURE(environment.update(1));
}

TEST(Environment, ToGlobalLocal) {
    std::ifstream configStream{"../config.json"};
    nlohmann::json j;
    configStream >> j;
    controller::Environment environment{j.get<controller::GameConfig>()};
    model::Vec vec{10,10};
    EXPECT_DOUBLE_EQ((environment.toGlobal(environment.toLocal(vec))-vec).norm(), 0);
    EXPECT_DOUBLE_EQ((environment.toLocal(environment.toGlobal(vec))-vec).norm(), 0);
}

#endif //TEST_ENVIRONMENT_HPP
