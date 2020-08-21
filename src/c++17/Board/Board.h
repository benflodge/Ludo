#pragma once
#include <vector>
#include "../Space/Space.h"

enum class SpaceType;

inline const int SECTIONS = 4;
inline const int BOARD_SIZE = 56;
inline const int ZONE_SIZE = BOARD_SIZE / SECTIONS;
inline const int RED_START = 0;
inline const int GREEN_START = 14;
inline const int ORANGE_START = 28;
inline const int PURPLE_START = 42;

class Board
{
    public:
		Board();
		Space* at(int i);
		Space* operator[](int i);
		int getStart(SpaceColour colour);
    private:
		std::vector<Space> m_board;
		Space setBoardSpace(int i);
		SpaceType computeSpaceType(int i);
};

