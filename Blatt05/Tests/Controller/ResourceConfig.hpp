#ifndef TEST_RESOURCECONFIG_HPP
#define TEST_RESOURCECONFIG_HPP

#include "../../Controller/ResourceConfig.hpp"
#include <fstream>

TEST(ResourceConfig, ReadFail) {
    std::ifstream notValid{"Tests/highscore_test.json"}, config{"config.json"};
    nlohmann::json j1, j2;
    notValid >> j1;
    config >> j2;
    EXPECT_THROW(j1.get<controller::ResourceConfig>(), nlohmann::json::exception);
    EXPECT_THROW(j2.get<controller::ResourceConfig>(), nlohmann::json::exception);
    EXPECT_NO_FATAL_FAILURE(j2.at("resource").get<controller::ResourceConfig>());
}

TEST(ResourceConfig, Read) {
    std::ifstream configFile{"config.json"};
    nlohmann::json j;
    configFile >> j;
    controller::ResourceConfig config =  j.at("resource").get<controller::ResourceConfig>();

    EXPECT_STREQ(config.font.c_str(), "Res/harry_p.ttf");
    EXPECT_STREQ(config.textures.player.c_str(), "Res/harry.png");
    EXPECT_STREQ(config.textures.obstacles.top.c_str(), "Res/dementor.png");
}

#endif
