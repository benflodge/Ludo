#include <iostream>
#include <memory>
#include <array>
#include <math.h>
#include "../SpaceColour/SpaceColour.h"
#include "../SpaceType/SpaceType.h"
#include "../Counter/Counter.h"
#include "Player.h"

Player::Player(SpaceColour c) :
    m_colour(c),
    m_counters
    {
        std::shared_ptr<Counter>(new Counter(c)),
        std::shared_ptr<Counter>(new Counter(c)),
        std::shared_ptr<Counter>(new Counter(c)),
        std::shared_ptr<Counter>(new Counter(c))
    } {}

SpaceColour Player::getColour()
{
    return m_colour;
}

void Player::setColour(SpaceColour colour)
{
    m_colour = colour;
}



