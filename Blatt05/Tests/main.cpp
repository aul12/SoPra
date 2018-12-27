#include "gtest/gtest.h"

#include "Util/Vector.h"
#include "Util/Rectangle.hpp"
#include "Model/GameItem.hpp"
#include "Model/Player.hpp"
#include "Model/Obstacle.hpp"
#include "Model/Item.hpp"
#include "Controller/GameConfig.hpp"
#include "Controller/ResourceConfig.hpp"
#include "Controller/Config.hpp"
#include "Controller/Environment.hpp"
#include "Model/HighscoreSaver.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

