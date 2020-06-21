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
	if(colour != SpaceColour::RED) allSpacesAreRed = false;
    }

    ASSERT_EQ (allSpacesAreRed, true);
}

TEST (BoardTest, TheSecondQuaterSpacesAreGreen) {
    Board board;
    int sectionSize = board.getSize() / 4;
    bool allSpacesAreGreen = true;
    for(int i = sectionSize; i < (sectionSize * 2); i++)
    {
	SpaceColour colour = board.at(i).getColour();
	if(colour != SpaceColour::GREEN) allSpacesAreGreen = false;
    }

    ASSERT_EQ (allSpacesAreGreen, true);
}

TEST (BoardTest, TheThirdQuaterSpacesAreOrange) {
    Board board;
    int sectionSize = board.getSize() / 4;
    bool allSpacesAreOrange = true;
    for(int i = sectionSize * 2; i < (sectionSize * 3); i++)
    {
	SpaceColour colour = board.at(i).getColour();
	if(colour != SpaceColour::ORANGE) allSpacesAreOrange = false;
    }

    ASSERT_EQ (allSpacesAreOrange, true);
}


TEST (BoardTest, TheFouthQuaterSpacesArePurple) {
    Board board;
    int boardSize = board.getSize();
    int sectionSize = boardSize / 4;
    bool allSpacesArePurple = true;
    for(int i = sectionSize * 3; i < boardSize; i++)
    {
	SpaceColour colour = board.at(i).getColour();
	if(colour != SpaceColour::PURPLE) allSpacesArePurple = false;
    }

    ASSERT_EQ (allSpacesArePurple, true);
}

TEST (BoardTest, TheFirstSpaceInEachSectionIsStart) {
    Board board;
    int startSpaceCount = 0;
    
    for(int i = 0; i < board.getSize(); i+=14)
    {
	SpaceType type = board.at(i).getType();
	if(type == SpaceType::START){
	    startSpaceCount ++;
	}
    }

    ASSERT_EQ (startSpaceCount, 4);
}

