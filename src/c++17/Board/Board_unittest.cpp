#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <math.h>
#include "gtest/gtest.h"
#include "Board.cpp"

 TEST(BoardTest, TheFirstQuaterSpacesAreRed)
 {
     Board board;
     int sectionSize = BOARD_SIZE / 4;
     bool allSpacesAreRed = true;

     for (int i = 0; i < sectionSize; i++)
     {
         SpaceColour colour = board.at(i)->getColour();
         if (colour != SpaceColour::RED)
             allSpacesAreRed = false;
     }

     ASSERT_EQ(allSpacesAreRed, true);
 }

 TEST(BoardTest, TheSecondQuaterSpacesAreGreen)
 {
     Board board;
     int sectionSize = BOARD_SIZE / 4;
     bool allSpacesAreGreen = true;

     for (int i = sectionSize; i < (sectionSize * 2); i++)
     {
         SpaceColour colour = board.at(i)->getColour();
         if (colour != SpaceColour::GREEN)
             allSpacesAreGreen = false;
     }
     ASSERT_EQ(allSpacesAreGreen, true);
 }

 TEST(BoardTest, TheThirdQuaterSpacesAreOrange)
 {
     Board board;
     int sectionSize = BOARD_SIZE / 4;
     bool allSpacesAreOrange = true;

     for (int i = sectionSize * 2; i < (sectionSize * 3); i++)
     {
         SpaceColour colour = board.at(i)->getColour();
         if (colour != SpaceColour::ORANGE)
             allSpacesAreOrange = false;
     }
     ASSERT_EQ(allSpacesAreOrange, true);
 }

 TEST(BoardTest, TheFouthQuaterSpacesArePurple)
 {
     Board board;
     int sectionSize = BOARD_SIZE / 4;
     bool allSpacesArePurple = true;

     for (int i = sectionSize * 3; i < BOARD_SIZE; i++)
     {
         SpaceColour colour = board.at(i)->getColour();
         if (colour != SpaceColour::PURPLE)
             allSpacesArePurple = false;
     }
     ASSERT_EQ(allSpacesArePurple, true);
 }

 TEST(BoardTest, BoardHas48NormalSpaces)
 {
     Board board;
     int normalSpaces = 0;

     for (int i = 0; i < BOARD_SIZE; i++)
     {
         SpaceType type = board.at(i)->getType();
         if (type == SpaceType::NORMAL)
             normalSpaces++;
     }
     ASSERT_EQ(normalSpaces, 48);
 }

 TEST(BoardTest, TheFirstSpaceInEachSectionIsStart)
 {
     Board board;
     int sectionSize = BOARD_SIZE / 4;
     int startSpaceCount = 0;

     for (int i = 0; i < BOARD_SIZE; i += sectionSize)
     {
         SpaceType type = board.at(i)->getType();
         if (type == SpaceType::START)
         {
             startSpaceCount++;
         }
     }
     ASSERT_EQ(startSpaceCount, 4);
 }

 TEST(BoardTest, TheLastSpaceInEachSectionIsEnd)
 {
     Board board;
     int sectionSize = BOARD_SIZE / 4;
     int endSpaceCount = 0;

     for (int i = 13; i < BOARD_SIZE; i += sectionSize)
     {
         SpaceType type = board.at(i)->getType();
         if (type == SpaceType::END)
         {
             endSpaceCount++;
         }
     }
     ASSERT_EQ(endSpaceCount, 4);
 }
