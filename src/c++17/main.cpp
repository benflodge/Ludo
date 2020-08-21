#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <utility>
#include <assert.h>
#include "SpaceColour/SpaceColour.h"
#include "HomeRun/HomeRun.h"
#include "Player/Player.h"
#include "Board/Board.h"
#include "Game/Game.h"

int main (int argc, char **argv)
{
    size_t players = 4;
    std::srand(std::time(nullptr));
    Game game = Game{players};

    bool playing = true;
    while (playing)
    {
        // take in turns to roll dice
        for (size_t i = 0; i < players; i++)
        {
            if(!playing) break;

            Player* player = game.getPlayer(i);
            int rollResult = Game::rollDice();
            bool moved = false;
            std::cout << "Player: " << i << " Rolls: " << rollResult << std::endl;
            for (int j = 0; j < COUNTERS; j++)
            {
                Counter* counter = player->getCounter(j);
                int currentPosition = counter->getPosition();
                if(currentPosition == HOME_POSITION)
                {
                    continue;
                }

                int newPosition = game.findNewCounterPosition(*counter, player->getColour(), rollResult);
                std::cout << "Player: " << i << " Current Position: " << currentPosition << " newPosition: " << newPosition <<std::endl;

                if(newPosition > 56)
                {
                    moved = game.moveHomeRunCounter(*counter, newPosition);
                    std::cout << "Player: " << i << " Rolls: " << rollResult << " Counter: " << j << " NewPosition on Home Run: " << newPosition << " Moved: " << moved <<std::endl;
                }
                else if(newPosition >= 0)
                {
                    moved = game.moveCounter(*counter, newPosition);
                    std::cout << "Player: " << i << " Rolls: " << rollResult << " Counter: " << j << " NewPosition: " << newPosition << " Moved: " << moved <<std::endl;
                }

                if(newPosition == HOME_POSITION)
                {
                    bool hasWon = true;
                    // Check others see if player has won
                    for (size_t k = 0; k < COUNTERS; k++)
                    {
                        Counter* counter = player->getCounter(k);
                        if(counter->getPosition() != HOME_POSITION)
                        {
                            hasWon = false;
                        }
                    }

                    if(hasWon)
                    {
                        std::cout << "Player: " << i << " Has Won!!!!" <<std::endl;
                        playing = false;
                        break;
                    }
                }

                if(moved){
                    // Only move one counter per roll!
                    break;
                }
            }
        }
    }
}
