#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <math.h>
#include "gtest/gtest.h"
#include "Space.cpp"


TEST(SpaceTest, TheSpaceColourIsCorrect)
{
    SpaceColour colour = SpaceColour::ORANGE;
    SpaceType type = SpaceType::NORMAL;
    Space space{ colour, type };

    ASSERT_EQ(space.getColour(), colour);
}


TEST(SpaceTest, TheSpaceTypeIsCorrect)
{
    SpaceColour colour = SpaceColour::ORANGE;
    SpaceType type = SpaceType::HOME;
    Space space{ colour, type };

    ASSERT_EQ(space.getType(), type);
}


TEST(SpaceTest, TheSpaceCanHaveCounterPointerSetandGet)
{
    SpaceColour colour = SpaceColour::ORANGE;
    SpaceType type = SpaceType::HOME;
    Space space{ colour, type };

    Counter counter{ colour };

    ASSERT_EQ(space.getCounter(), nullptr);

    space.setCounter(&counter);
    ASSERT_EQ(space.getCounter(), &counter);
}
