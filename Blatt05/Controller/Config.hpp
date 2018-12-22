/**
 * @file Config.hpp
 * @author paul
 * @date 22.12.18
 * @brief Config @TODO
 *
 * @TODO
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>

namespace controller {
    class Config {
    public:
        explicit Config(std::string fname);

        struct {
            double accelerationUp;
            double mass;
            double width;
            double height;
            struct {
                double x, y;
            } initial;
        } player;
        struct {
            double width, height;
        };
        double gravity;
    };
}

#endif //TEST_CONFIG_HPP
