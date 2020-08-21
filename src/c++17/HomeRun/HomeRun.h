#pragma once
#include <vector>
#include "../Space/Space.h"

enum class SpaceType;

inline const int HOME_RUN_SIZE = 6;

class HomeRun
{
    public:
		HomeRun();
		HomeRun(SpaceColour colour);
		Space* at(int i);
		Space* operator[](int i);
    private:
		std::vector<Space> m_board;
		SpaceColour m_colour;
};

