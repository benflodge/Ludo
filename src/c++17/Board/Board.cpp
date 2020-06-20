#include <vector>

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
	Space() : type(SpaceType::NORMAL), colour(SpaceColour::RED) {}
	Space(SpaceType t) : type(t), colour(SpaceColour::RED) {}
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

class Board
{
    public: 
	Board() : board(56)
	{
	    for(int i = 0; i < 4; i++)
	    {
		board[i] = Space(SpaceType::START);
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
