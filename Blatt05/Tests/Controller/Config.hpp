#ifndef TEST_CONFIG_HPP
#define TEST_CONFIG_HPP

#include "../../Controller/GameConfig.hpp"
#include <fstream>

TEST(GameConfig, ReadFail) {
    std::ifstream notValid{"../Tests/highscore_test.json"}, config{"../config.json"};
    nlohmann::json j1, j2;
    notValid >> j1;
    config >> j2;
    EXPECT_THROW(j1.get<controller::GameConfig>(), std::runtime_error);
    EXPECT_NO_FATAL_FAILURE(j2.get<controller::GameConfig>());
}

TEST(GameConfig, Read) {
    std::ifstream configFile{"../config.json"};
    nlohmann::json j;
    configFile >> j;
    auto config =  j.get<controller::GameConfig>();

    EXPECT_DOUBLE_EQ(config.gravity, 9.81);
    EXPECT_DOUBLE_EQ(config.player.mass, 92);
    EXPECT_DOUBLE_EQ(config.environment.width, 44);
    EXPECT_DOUBLE_EQ(config.environment.height, 24);
}

#endif //TEST_CONFIG_HPP
