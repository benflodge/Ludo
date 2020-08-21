#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <math.h>
#include "gtest/gtest.h"
#include "HomeRun.cpp"

TEST (HomeRunTest, HomeRunHas5NormalSpaces) {
    HomeRun board;
    int normalSpaces = 0;

    for(int i = 0; i < HOME_RUN_SIZE; i++)
    {
	SpaceType type = board.at(i).getType();
	if(type == SpaceType::NORMAL) normalSpaces ++;
    }
    ASSERT_EQ (normalSpaces, 48);
}

TEST (HomeRunTest, TheFirstSpaceInEachSectionIsStart) {
    HomeRun board;
    int sectionSize = HOME_RUN_SIZE / 4;
    int startSpaceCount = 0;

    for(int i = 0; i < HOME_RUN_SIZE; i+=sectionSize)
    {
	SpaceType type = board.at(i).getType();
	if(type == SpaceType::START){
	    startSpaceCount ++;
	}
    }
    ASSERT_EQ (startSpaceCount, 4);
}

TEST (HomeRunTest, TheLastSpaceInEachSectionIsEnd) {
    HomeRun board;
    int sectionSize = HOME_RUN_SIZE / 4;
    int endSpaceCount = 0;

    for(int i = 13; i < HOME_RUN_SIZE; i+=sectionSize)
    {
	SpaceType type = board.at(i).getType();
	if(type == SpaceType::END){
	    endSpaceCount ++;
	}
    }
    ASSERT_EQ (endSpaceCount, 4);
}

TEST (HomeRunTest, PurpleHomeRunHas5Spaces) {
    HomeRun board;
    int runSpaceCount = 0;

    for(int i = 0; i < HOME_RUN_SIZE; i++)
    {
	SpaceType type = board.atPurpleRun(i).getType();
	if(type == SpaceType::RUN){
	    runSpaceCount ++;
	}
    }
    ASSERT_EQ (runSpaceCount, 5);
}

TEST (HomeRunTest, LastSpaceInPurpleRunIsHome) {
    HomeRun board;
    Space space = board.atPurpleRun(5);
    SpaceType type = space.getType();
    SpaceColour colour = space.getColour();

    ASSERT_EQ (colour, SpaceColour::PURPLE);
    ASSERT_EQ (type, SpaceType::HOME);
}

