#include <vector>
#include <math.h>

enum class SpaceType { 
    NORMAL, 
    START//, 
    //END, 
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
	Space(SpaceColour c) : colour(c) {}
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
		if(i % 14 == 0) {
		    type = SpaceType::START;
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
};

