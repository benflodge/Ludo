#include <iostream>
#include <memory>
#include <vector>
#include <math.h>

#include "../SpaceColour/SpaceColour.h"
#include "../SpaceType/SpaceType.h"
#include "../Space/Space.h"

#include "Board.h"

Board::Board() : m_board(TOTAL_BOARD_SIZE)
{
	for(int i = 0; i < TOTAL_BOARD_SIZE; i++)
	{
	if (i < BOARD_SIZE)
	{
		m_board[i] = setBoardSpace(i);
	}
	else
	{
		m_board[i] = setRunSpace(i);
	}
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

Space Board::setRunSpace(int i)
{
	int section = (int)floor((i - BOARD_SIZE) / HOME_RUN_SIZE);
	SpaceColour colour = static_cast<SpaceColour>(section);
	SpaceType type = ((i - BOARD_SIZE) % 6) == 5 ? SpaceType::HOME: SpaceType::RUN;
	return Space(colour, type);
}

Space Board::at(int position)
{
	return m_board[position];
}

Space Board::atRedHome()
{
	return m_board[0];
}

Space Board::atGreenHome()
{
	return m_board[14];
}

Space Board::atOrangeHome()
{
	return m_board[28];
}

Space Board::atPurpleHome()
{
	return m_board[42];
}

Space Board::atRedRun(int position)
{
	return m_board[BOARD_SIZE + position];
}

Space Board::atGreenRun(int position)
{
	return m_board[BOARD_SIZE + HOME_RUN_SIZE + position];
}

Space Board::atOrangeRun(int position)
{
	return m_board[BOARD_SIZE + (HOME_RUN_SIZE * 2) + position];
}

Space Board::atPurpleRun(int position)
{
	return m_board[BOARD_SIZE + (HOME_RUN_SIZE * 3) + position];
}



