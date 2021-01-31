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
        Counter(c),
        Counter(c),
        Counter(c),
        Counter(c)
    } {}

SpaceColour Player::getColour()
{
    return m_colour;
}

Counter* Player::getCounter(int i)
{
    return &m_counters[i];
}


