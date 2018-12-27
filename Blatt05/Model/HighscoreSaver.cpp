/**
 * @file HighscoreSaver.cpp
 * @author paul
 * @date 23.12.18
 * @brief Implementation of the HighscoreSaver class
 */

#include "HighscoreSaver.hpp"

#include <fstream>
#include <filesystem>
#include <utility>
#include <algorithm>

#include "../Lib/json.hpp"

namespace model {
    HighscoreSaver::HighscoreSaver(const std::string &fname) : fname{fname}, highscore{} {
        // Create an empty json file
        if (!std::filesystem::exists(fname)) {
            nlohmann::json jsonRoot = nlohmann::json::array();
            std::ofstream ofstream(fname);
            ofstream << jsonRoot.dump(INDENT);
            ofstream.close();
            return;
        }

        // Read the contents of the file
        std::ifstream ifstream{fname};
        nlohmann::json jsonRoot;
        if (!ifstream.good()) {
            throw std::runtime_error("File exists but not good!");
        }

        try {
            ifstream >> jsonRoot;
        } catch (nlohmann::json::exception &e) {
            throw std::runtime_error(e.what());
        }
        if (!jsonRoot.is_array()) {
            throw std::runtime_error("Highscore root element is not an array");
        }

        highscore.reserve(jsonRoot.size());
        for (const auto &entry: jsonRoot) {
            if(!entry.is_object()) {
                throw std::runtime_error("Malformed json, not every entry is an object");
            }
            try{
                highscore.push_back(std::make_pair(entry.at("points").get<int>(), entry.at("name").get<std::string>()));
            } catch(nlohmann::json::exception &e) {
                throw std::runtime_error("Malformed json, entries missing or from wrong type");
            }
        }
    }

    void HighscoreSaver::insert(int points, std::string name) {
        highscore.push_back(std::make_pair(points, name));
        nlohmann::json jsonRoot = nlohmann::json::array();
        for (const auto &entry : highscore) {
            auto newJson = nlohmann::json::object();
            newJson["points"] = entry.first;
            newJson["name"] = entry.second;
            jsonRoot.push_back(newJson);
        }

        std::ofstream ofstream(fname, std::ostream::trunc);
        ofstream << jsonRoot.dump(INDENT);
        ofstream.close();
    }

    auto HighscoreSaver::retrieveHighscore(int numberOfEntries) -> std::vector<std::pair<int, std::string>> {
        assert(numberOfEntries >= 0);

        std::sort(highscore.begin(), highscore.end(), [](const auto &a, const auto &b){
            return a > b;
        });
        auto length = std::min<std::size_t >(static_cast<size_t>(numberOfEntries), highscore.size());
        return {highscore.begin(), highscore.begin()+length};
    }
}
