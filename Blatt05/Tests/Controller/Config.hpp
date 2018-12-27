#ifndef TEST_CONFIG_HPP
#define TEST_CONFIG_HPP

#include "../../Controller/Config.hpp"

TEST(Config, Open) {
    EXPECT_THROW(controller::Config{"NOT_A_FILE"}, std::runtime_error);
    EXPECT_THROW(controller::Config{"Tests"}, std::runtime_error);
    EXPECT_THROW(controller::Config{"highscore.json"}, std::runtime_error);
    EXPECT_NO_THROW(controller::Config{"config.json"});
}

#endif //TEST_CONFIG_HPP
