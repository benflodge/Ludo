#include <iostream>
#include <memory>
#include <vector>
#include <math.h>

#include "../SpaceColour/SpaceColour.h"
#include "../SpaceType/SpaceType.h"
#include "../Space/Space.h"

#include "Board.h"

Board::Board() : m_board(BOARD_SIZE)
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		m_board[i] = setBoardSpace(i);
	}
}

Space Board::setBoardSpace(int i)
{
	int section = (int)floor(i / ZONE_SIZE);
	SpaceColour colour = static_cast<SpaceColour>(section);
	SpaceType type = computeSpaceType(i);

	return Space(colour, type);
}

SpaceType Board::computeSpaceType(int i)
{
	SpaceType type;
	switch (i % ZONE_SIZE)
	{
		case 0:
			type = SpaceType::START;
			break;
		case 13:
			type = SpaceType::END;
			break;
		default:
			type = SpaceType::NORMAL;
	}
	return type;
}

Space* Board::at(int i)
{
	return &m_board[i];
}

Space* Board::operator[](int i)
{
	return &m_board[i];
}

int Board::getStart(SpaceColour colour)
{
	int startPosition = 0;
	switch(colour)
	{
		case SpaceColour::RED:
			startPosition = RED_START;
		case SpaceColour::GREEN:
			startPosition = GREEN_START;
		case SpaceColour::ORANGE:
			startPosition = RED_START;
		case SpaceColour::PURPLE:
			startPosition = RED_START;
	}
	return startPosition;
}
