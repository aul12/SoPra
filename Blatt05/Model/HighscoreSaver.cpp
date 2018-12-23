/**
 * @file HighscoreSaver.cpp
 * @author paul
 * @date 23.12.18
 * @brief Implementation of the HighscoreSaver class
 */

#include "HighscoreSaver.hpp"

#include <fstream>

namespace model {
    HighscoreSaver::HighscoreSaver(std::string fname) : fname{fname} {
        /*
         * @TODO there might be some issues if the file exists but eg. permissions are wrong using stat() would
         * help but this probably won't work on windows (who the fuck needs POSIX compatibility).
         */
        std::ifstream ifstream{fname};

        if (ifstream.good()) {
            try {
                ifstream >> jsonRoot;
            } catch (json::exception e) {
                throw std::runtime_error(e.what());
            }
            if(!jsonRoot.is_array()) {
                throw std::runtime_error("Highscore root element is not an array");
            }
        } else {
            jsonRoot = json::array();
            ifstream.close();
            std::ofstream ofstream(fname);
            ofstream << jsonRoot.dump(INDENT);
            ofstream.close();
        }
    }

    void HighscoreSaver::insert(int points, std::string name) {
        json newEntry = json::object();
        newEntry["name"] = name;
        newEntry["points"] = points;
        jsonRoot.push_back(newEntry);

        std::ofstream ofstream(fname, std::ostream::trunc);
        ofstream << jsonRoot.dump(INDENT);
        ofstream.close();
    }

    auto HighscoreSaver::retrieveHighscore(int numberOfEntries) const -> std::vector<std::tuple<std::string, int>> {
        std::vector<std::tuple<std::string, int>> entries;
        entries.reserve(jsonRoot.size());

        for (const auto &entry : jsonRoot) {
            if(!entry.is_object()) {
                throw std::runtime_error("Malformed json, not every entry is an object");
            }
            try{
                entries.push_back(std::make_tuple(entry["name"].get<std::string>(), entry["points"].get<int>()));
            } catch(json::exception e) {
                throw std::runtime_error("Malformed json, entries missing or from wrong type");
            }
        }

        std::sort(entries.begin(), entries.end(), [](const auto &a, const auto &b){
            return std::get<1>(b) < std::get<1>(a);
        });

        int length = std::min<int>(numberOfEntries, entries.size());

        return {entries.begin(), entries.begin()+length};
    }
}
