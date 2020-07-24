#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include "../SpaceColour/SpaceColour.h"
#include "../SpaceType/SpaceType.h"
#include "../Space/Space.h"
#include "Counter.h"

Counter::Counter(SpaceColour c) : m_colour(c) {}
SpaceColour Counter::getColour()
{
	return m_colour;
}

Space& Counter::getSpace()
{
	return *m_space;
}

void Counter::setSpace(Space* space)
{
	m_space = space;
}
