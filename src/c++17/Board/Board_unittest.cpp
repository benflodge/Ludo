#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "gtest/gtest.h"
#include "Board.cpp"

TEST (BoardTest, BoardHas56Spaces) {
    Board board;
    ASSERT_EQ (board.getSize(), 56);
}


TEST (BoardTest, TheFirstQuaterSpacesAreRed ) {
    Board board;
    int sectionSize = board.getSize() / 4;
    bool allSpacesAreRed = true;
    for(int i = 0; i < sectionSize; i++)
    {
	SpaceColour colour = board.at(i).getColour();
	std::cout << "Colour: " << (int)colour << (int)SpaceColour::RED << std::endl;
	if(colour != SpaceColour::RED) allSpacesAreRed = false;
    }

    ASSERT_EQ (allSpacesAreRed, true);
}

TEST (BoardTest, BoardHas4StartSpaces) {
    Board board;
    int startSpaceCount = 0;
    
    for(int i = 0; i < board.getSize(); i++)
    {
	SpaceType type = board.at(i).getType();
	if(type == SpaceType::START){
	    startSpaceCount ++;
	}
    }

    ASSERT_EQ (startSpaceCount, 4);
}

