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
    EXPECT_NO_THROW(model::HighscoreSaver{"../Tests/highscore_test.json"});
    EXPECT_THROW(model::HighscoreSaver{"../main.cpp"}, std::runtime_error);
    EXPECT_THROW(model::HighscoreSaver{"../config.json"}, std::runtime_error);
}

TEST(HighscoreSaver, Insert) {
    EXPECT_NO_THROW(model::HighscoreSaver{"test.json"}.insert(25, "Third"));
}

TEST(HighscoreSaver, Retrieve) {
    model::HighscoreSaver highscoreSaver{"../Tests/highscore_test.json"};
    std::vector<std::tuple<std::string, int>> a,b,c,d;
    EXPECT_NO_THROW(a = highscoreSaver.retrieveHighscore(0));
    EXPECT_NO_THROW(b = highscoreSaver.retrieveHighscore(1));
    EXPECT_NO_THROW(c = highscoreSaver.retrieveHighscore(2));
    EXPECT_NO_THROW(d = highscoreSaver.retrieveHighscore(3));
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(c.size(), 2);
    EXPECT_EQ(d.size(), 2);
    EXPECT_EQ(std::get<0>(b[0]), "First");
    EXPECT_EQ(std::get<0>(c[0]), "First");
    EXPECT_EQ(std::get<0>(d[0]), "First");
    EXPECT_EQ(std::get<1>(b[0]), 100);
    EXPECT_EQ(std::get<1>(c[0]), 100);
    EXPECT_EQ(std::get<1>(d[0]), 100);
    EXPECT_EQ(std::get<0>(c[1]), "Second");
    EXPECT_EQ(std::get<0>(d[1]), "Second");
    EXPECT_EQ(std::get<1>(c[1]), 50);
    EXPECT_EQ(std::get<1>(d[1]), 50);
}

#endif
