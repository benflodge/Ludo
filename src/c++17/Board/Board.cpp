#include <iostream>
#include <vector>
#include <math.h>

enum class SpaceType { 
    NORMAL, 
    START, 
    END, 
    //RUN, 
    //HOME 
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

const int BOARD_SIZE = 56;
const int ZONE_SIZE = BOARD_SIZE / 4;

class Board
{
    public: 
	Board() : board(BOARD_SIZE)
	{
	    for(int i = 0; i < BOARD_SIZE; i++)
	    {
		int section = (int)floor(i / ZONE_SIZE);
		SpaceColour colour = static_cast<SpaceColour>(section);
		SpaceType type;
		int modResult = i % 14;
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
	}

	int getSize()
	{
	    return board.size();
	}

	Space at(int idx)
	{
	    return board[idx];
	}

    private: 
	std::vector<Space> board;
//	std::vector<Space> redRun;
//    	std::vector<Space> greenRun;
//	std::vector<Space> orangeRun;
//	std::vector<Space> purpleRun;

};

