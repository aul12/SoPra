#ifndef TEST_CONFIG_HPP
#define TEST_CONFIG_HPP

#include "../../Controller/Config.hpp"

TEST(Config, ReadFail) {
    EXPECT_THROW(controller::Config{"NOT_A_FILE"}, std::runtime_error);
    EXPECT_THROW(controller::Config{"../main.cpp"}, std::runtime_error); // Not a valid json
    EXPECT_NO_FATAL_FAILURE(controller::Config{"../config.json"});
}

TEST(Config, Read) {
    controller::Config config{"../config.json"};

    EXPECT_DOUBLE_EQ(config.gravity, 9.81);
    EXPECT_DOUBLE_EQ(config.player.mass, 92);
    EXPECT_DOUBLE_EQ(config.environment.width, 44);
    EXPECT_DOUBLE_EQ(config.environment.height, 24);
}

#endif //TEST_CONFIG_HPP
