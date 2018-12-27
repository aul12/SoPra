#ifndef TEST_HIGHSCORESAVER_HPP
#define TEST_HIGHSCORESAVER_HPP

#include "../../Model/HighscoreSaver.hpp"

TEST(HighscoreSaver, Create) {
    // Create an random filename which (hopefully doesn't exist)
    std::stringstream stringstream;
    std::srand(static_cast<unsigned int>(time(nullptr)));
    stringstream << "/tmp/test_" << std::rand() << ".json";
    EXPECT_NO_THROW(model::HighscoreSaver{stringstream.str()});
}

TEST(HighscoreSaver, Open) {
    EXPECT_THROW(model::HighscoreSaver{"main.cpp"}, std::runtime_error);
    EXPECT_THROW(model::HighscoreSaver{"config.json"}, std::runtime_error);
    EXPECT_THROW(model::HighscoreSaver{"Tests"}, std::runtime_error);
    EXPECT_NO_THROW(model::HighscoreSaver{"Tests/highscore_test.json"});
}

TEST(HighscoreSaver, Insert) {
    EXPECT_NO_THROW(model::HighscoreSaver{"/tmp/test.json"}.insert(25, "Third"));
}

TEST(HighscoreSaver, Retrieve) {
    model::HighscoreSaver highscoreSaver{"Tests/highscore_test.json"};
    std::vector<std::pair<int, std::string>> a,b,c,d;
    EXPECT_NO_THROW(a = highscoreSaver.retrieveHighscore(0));
    EXPECT_NO_THROW(b = highscoreSaver.retrieveHighscore(1));
    EXPECT_NO_THROW(c = highscoreSaver.retrieveHighscore(2));
    EXPECT_NO_THROW(d = highscoreSaver.retrieveHighscore(3));
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(c.size(), 2);
    EXPECT_EQ(d.size(), 2);
    EXPECT_EQ(b[0].first, 100);
    EXPECT_EQ(c[0].first, 100);
    EXPECT_EQ(d[0].first, 100);
    EXPECT_EQ(b[0].second, "First");
    EXPECT_EQ(c[0].second, "First");
    EXPECT_EQ(d[0].second, "First");
    EXPECT_EQ(c[1].first, 50);
    EXPECT_EQ(c[1].first, 50);
    EXPECT_EQ(c[1].second, "Second");
    EXPECT_EQ(d[1].second, "Second");
}

#endif
