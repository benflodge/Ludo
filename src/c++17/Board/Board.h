#pragma once
#include <vector>
#include "../Space/Space.h"

enum class SpaceType;

inline const int SECTIONS = 4;
inline const int BOARD_SIZE = 56;
inline const int ZONE_SIZE = BOARD_SIZE / SECTIONS;
inline const int HOME_RUN_SIZE = 6;
inline const int TOTAL_BOARD_SIZE = HOME_RUN_SIZE * SECTIONS + BOARD_SIZE;

class Board
{
    public:
		Board();
		Space setBoardSpace(int i);
		SpaceType computeSpaceType(int i);
		Space setRunSpace(int i);
		Space at(int position);
		Space atRedHome();
		Space atGreenHome();
		Space atOrangeHome();
		Space atPurpleHome();
		Space atRedRun(int position);
		Space atGreenRun(int position);
		Space atOrangeRun(int position);
		Space atPurpleRun(int position);
    private:
		std::vector<Space> m_board;
};

