#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <math.h>
#include "gtest/gtest.h"
#include "Counter.cpp"

TEST (CounterTest, TheCounterColourIsCorrect) 
{
    SpaceColour colour = SpaceColour::ORANGE;
    Counter counter{ colour };

    ASSERT_EQ(counter.getColour(), colour);
}

TEST(CounterTest, TheCounterStartingPositionIsOffBoard)
{
    Counter counter{ SpaceColour::ORANGE };
    ASSERT_EQ(counter.getPosition(), OFF_BOARD);
}

TEST(CounterTest, TheCounterPositionsCanBeSetAndGet)
{
    Counter counter{ SpaceColour::ORANGE };
    int position = 21;
    counter.setPosition(position);
    ASSERT_EQ(counter.getPosition(), position);
}
