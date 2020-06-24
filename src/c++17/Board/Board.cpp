#include <iostream>
#include <vector>
#include <math.h>

// game
// players => 2 - 4
// turn => player

// player
// counters => counter
// rollDice
// chooseCounter

// counter
// is colour
// positionOnBoard
// move

enum class SpaceType { 
    NORMAL, 
    START, 
    END, 
    RUN, 
    HOME 
};

enum class SpaceColour {
    RED,
    GREEN,
    ORANGE,
    PURPLE
};

class Space
{
    public:
	Space() {}
	Space(SpaceColour c, SpaceType t) : colour(c), type(t) {}
        SpaceType getType()
	{
	    return type;
	}
	SpaceColour getColour()
	{
	    return colour;
	}

    private:
	SpaceType type;
	SpaceColour colour;
};

const int SECTIONS = 4;
const int BOARD_SIZE = 56;
const int ZONE_SIZE = BOARD_SIZE / SECTIONS;
const int HOME_RUN_SIZE = 6;
const int TOTAL_BOARD_SIZE = HOME_RUN_SIZE * SECTIONS + BOARD_SIZE;

class Board
{
    public: 
	Board() : board(TOTAL_BOARD_SIZE)
	{
	    for(int i = 0; i < BOARD_SIZE; i++)
	    {
		int section = (int)floor(i / ZONE_SIZE);
		SpaceColour colour = static_cast<SpaceColour>(section);
		SpaceType type;
		int modResult = i % ZONE_SIZE;
		switch (modResult) {
    		case 0:
		    type = SpaceType::START;
		    break;
		case 13:
		    type = SpaceType::END;
		    break;
		default:
		    type = SpaceType::NORMAL;
		}
		board[i] = Space(colour, type);
	    }

	    for(int i = BOARD_SIZE; i < TOTAL_BOARD_SIZE; i++)
	    {
		int section = (int)floor(i - BOARD_SIZE / HOME_RUN_SIZE);
		SpaceColour colour = static_cast<SpaceColour>(section);
		SpaceType type = (i - BOARD_SIZE) % 6 == 0 ? SpaceType::RUN : SpaceType::HOME; 
		board[i] = Space(colour, type);
	    }
	}

	Space at(int idx)
	{
	    return board[idx];
	}

    private: 
	std::vector<Space> board;
};

