#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include "../SpaceColour/SpaceColour.h"
#include "../SpaceType/SpaceType.h"
#include "../Counter/Counter.h"
#include "Space.h"

Space::Space() {}
Space::Space(SpaceColour c, SpaceType t) : m_colour(c), m_type(t), m_counter(nullptr) {}
SpaceType Space::getType()
{
	return m_type;
}

SpaceColour Space::getColour()
{
	return m_colour;
}

Counter* Space::getCounter()
{
	return m_counter;
}

void Space::setCounter(Counter* counter)
{
	m_counter = counter;
}
