#include <iostream>
#include <memory>
#include <vector>
#include <math.h>

#include "../SpaceColour/SpaceColour.h"
#include "../SpaceType/SpaceType.h"
#include "../Space/Space.h"

#include "HomeRun.h"

HomeRun::HomeRun(){}

HomeRun::HomeRun(SpaceColour colour) : m_colour(colour), m_board(HOME_RUN_SIZE)
{
	for(int i = 0; i < HOME_RUN_SIZE; i++)
	{
		SpaceType type = ((i - HOME_RUN_SIZE) % 6) == 5 ? SpaceType::HOME: SpaceType::RUN;
		m_board[i] = Space(m_colour, type);
	}
}

Space* HomeRun::at(int i)
{
	return &m_board[i];
}

Space* HomeRun::operator[](int i)
{
	return &m_board[i];
}