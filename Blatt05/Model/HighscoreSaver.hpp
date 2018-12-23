/**
 * @file HighscoreSaver.hpp
 * @author paul
 * @date 23.12.18
 * @brief Declaration of the HighscoreSaver class
 */

#ifndef HIGHSCORESAVER_HPP
#define HIGHSCORESAVER_HPP

#include <string>
#include <vector>
#include <tuple>

#include "../Lib/json.hpp"

using json = nlohmann::json;

namespace model {
    class HighscoreSaver {
    public:
        /**
         * Create a new highscore saver, if the file referenced by fname exists it is used as an initial list,
         * if not a new file is created
         * @param fname the path to the json file
         */
        HighscoreSaver(std::string fname);

        /**
         * Insert a new highscore entry, this also updates the highscore file
         * @param points the amount of points the person scored
         * @param name the name of the person
         */
        void insert(int points, std::string name);

        /**
         * Retrieve the numberOfEntries best players, if there are less than numberOfEntries players only these are
         * returned.
         * @param numberOfEntries the maximum number of entries to return
         * @return a vector with each element containing an tuple of the name and the score, the vector is sorted by the score
         */
        auto retrieveHighscore(int numberOfEntries = 3) const -> std::vector<std::tuple<std::string, int>>;
    private:
        std::string fname;
        json jsonRoot;
        static constexpr int INDENT = 4;
    };
}

#endif
