#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <math.h>
#include "gtest/gtest.h"
#include "Player.cpp"


TEST(PlayerTest, ThePlayerColourIsCorrect)
{
    SpaceColour colour = SpaceColour::ORANGE;
    Player player{ colour };

    ASSERT_EQ(player.getColour(), colour);
}

TEST(PlayerTest, ThePlayerReturnsPointersTo4Counters)
{
    SpaceColour colour = SpaceColour::ORANGE;
    Player player{ colour };

    for (size_t i = 0; i < 4; i++)
    {
        Counter* counter = player.getCounter(i);
        ASSERT_EQ(counter->getColour(), colour);
    }
}
