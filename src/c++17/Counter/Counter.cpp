#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include "../SpaceColour/SpaceColour.h"
#include "../SpaceType/SpaceType.h"
#include "../Space/Space.h"
#include "Counter.h"

Counter::Counter(SpaceColour c) : m_colour(c), m_position(OFF_BOARD) {}

SpaceColour Counter::getColour()
{
	return m_colour;
}

int Counter::getPosition()
{
	return m_position;
}

void Counter::setPosition(int position)
{
	m_position = position;
}
