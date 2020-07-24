#include <iostream>
#include "SpaceColour/SpaceColour.h"
#include "Player/Player.h"
#include "Board/Board.h"


int rollDice()
{
    return 1 + std::rand()/((RAND_MAX + 1u)/6);
}

int main (int argc, char **argv)
{
    Player louise = Player(SpaceColour::PURPLE);
    Player tobias = Player(SpaceColour::RED);
    Player ben = Player(SpaceColour::ORANGE);
    size_t playerCount = 3;

    Board board = Board();

    bool playing = true;

    while (playing)
    {
        // take in turns to roll dice
        for (size_t i = 0; i < playerCount; i++)
        {
            // IF player rolls 6 they may put a counter onto the board, at start position
            int result = rollDice();
            if(result == 6)
            {
                Space space = board.atRedHome();
                std::cout << "Player rolled a 6" <<  (int)space.getType() << (int)space.getColour() <<  std::endl;
            }
        }
    }

    std::cout << "done" << std::endl;
}
