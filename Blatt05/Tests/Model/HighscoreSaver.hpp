#ifndef TEST_HIGHSCORESAVER_HPP
#define TEST_HIGHSCORESAVER_HPP

#include "../../Model/HighscoreSaver.hpp"

TEST(HighscoreSaver, Create) {
    // Create an random filename which (hopefully doesn't exist)
    std::stringstream stringstream;
    std::srand(static_cast<unsigned int>(time(nullptr)));
    stringstream << "test_" << std::rand() << ".json";
    EXPECT_NO_THROW(model::HighscoreSaver{stringstream.str()});
}

TEST(HighscoreSaver, Open) {
    EXPECT_NO_THROW(model::HighscoreSaver{"../highscore.json"});
    EXPECT_THROW(model::HighscoreSaver{"../main.cpp"}, std::runtime_error);
    EXPECT_THROW(model::HighscoreSaver{"../config.json"}, std::runtime_error);
}

#endif
