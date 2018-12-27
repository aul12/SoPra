#ifndef TEST_GAMECONFIG_HPP
#define TEST_GAMECONFIG_HPP

#include "../../Controller/GameConfig.hpp"
#include <fstream>

TEST(GameConfig, ReadFail) {
    std::ifstream notValid{"Tests/highscore_test.json"}, config{"config.json"};
    nlohmann::json j1, j2;
    notValid >> j1;
    config >> j2;
    EXPECT_THROW(j1.get<controller::GameConfig>(), nlohmann::json::exception);
    EXPECT_THROW(j2.get<controller::GameConfig>(), nlohmann::json::exception);
    EXPECT_NO_FATAL_FAILURE(j2.at("game").get<controller::GameConfig>());
}

TEST(GameConfig, Read) {
    std::ifstream configFile{"config.json"};
    nlohmann::json j;
    configFile >> j;
    auto config =  j.at("game").get<controller::GameConfig>();

    EXPECT_DOUBLE_EQ(config.gravity, 9.81);
    EXPECT_DOUBLE_EQ(config.player.mass, 92);
    EXPECT_DOUBLE_EQ(config.environment.width, 44);
    EXPECT_DOUBLE_EQ(config.environment.height, 24);
}

#endif
