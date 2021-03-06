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
#include <utility>

namespace model {
    /**
     * Implements an interface between the highscore.json file and the program. All data gets also written to the disk.
     * This class is not safe if multiple instances of the game try to access the file.
     */
    class HighscoreSaver {
    public:
        /**
         * Create a new highscore saver, if the file referenced by fname exists it is used as an initial list,
         * if not a new file is created.
         * @param fname the path to the json file
         * @throws std::runtime_error if the file is not a valid json file.
         */
        HighscoreSaver(const std::string &fname);

        /**
         * Insert a new highscore entry, this also updates the highscore file
         * @param points the amount of points the person scored
         * @param name the name of the person
         */
        void insert(int points, std::string name);

        /**
         * Retrieve the numberOfEntries best players, if there are less than numberOfEntries players only these are
         * returned.
         * @param numberOfEntries the maximum number of entries to return, needs to be non negative
         * @return a vector with each element containing an the name and the score, the vector is sorted by the score (descending)
         */
        auto retrieveHighscore(int numberOfEntries = 3) -> std::vector<std::pair<int, std::string>>;
    private:
        std::string fname;
        std::vector<std::pair<int, std::string>> highscore;
        static constexpr int INDENT = 4; ///< Number of spaces to indent when writing the file
    };
}

#endif
