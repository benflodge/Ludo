#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <utility>
#include <assert.h>
#include "../SpaceColour/SpaceColour.h"
#include "../HomeRun/HomeRun.h"
#include "../Player/Player.h"
#include "../Board/Board.h"
#include "../Game/Game.h"

Game::Game(){};

Game::Game(size_t players)
{
    for (size_t i = 0; i < players; i++)
    {
        SpaceColour colour = static_cast<SpaceColour>(i);
        m_players.push_back(Player(colour));
        m_home_runs.emplace(colour, HomeRun(colour));
    }
}

Player* Game::getPlayer(int i)
{
    return &m_players[i];
}

int Game::findNewCounterPosition(Counter& counter, SpaceColour playerColour, int rollResult)
{
    bool canAddNew = Game::canAddNewCounter(rollResult);
    int counterPos = counter.getPosition();
    int startPosition = m_board.getStart(playerColour);
    int newPosition = -1;

    if(counterPos == OFF_BOARD && canAddNew)
    {
        // IF player rolls 6 they may put a counter onto
        // the board, at start position
        newPosition = startPosition;
    }
    else if (counterPos != OFF_BOARD)
    {
        // calculate new pos
        newPosition = counterPos + rollResult;
    }

    int endPosition = startPosition == 0 ? BOARD_SIZE : startPosition - 1;

    if(counterPos <= BOARD_SIZE && newPosition > endPosition)
    {
        // move onto home run:
        // 56 + 5 = new 61 - end 56 = 51
        newPosition = BOARD_SIZE + (newPosition - endPosition);
        assert(newPosition > BOARD_SIZE);
    }

    return newPosition;
}

bool Game::moveCounter(Counter& counter, int newPosition)
{
    Space* newSpace = m_board[newPosition];
    Counter* target = newSpace->getCounter();

    if(target && target->getColour() == counter.getColour())
    {
        return false;
    }
    else if (target)
    {
        std::cout << (int)counter.getColour() << " Player took: " << (int)target->getColour() << std::endl;
        target->setPosition(OFF_BOARD);
        removeCounterFromCurrentSpace(*target);
    }

    removeCounterFromCurrentSpace(counter);

    // Set counters new newSpace
    newSpace->setCounter(&counter);
    counter.setPosition(newPosition);

    return true;
}

bool Game::moveHomeRunCounter(Counter& counter, int newPosition)
{
    SpaceColour colour = counter.getColour();
    HomeRun& homeRun = m_home_runs[colour];
    Space* space = homeRun[newPosition];
    Counter* target = space->getCounter();

    if(target)
    {
        // Cannot move on top of another counter of the same colour
        return false;
    }
    else if (newPosition > BOARD_SIZE + HOME_RUN_SIZE)
    {
        // Need exact number to end the game
        return false;
    }

    if (newPosition == HOME_POSITION)
    {
        removeCounterFromCurrentSpace(counter);
        counter.setPosition(newPosition);
        std::cout << (int)counter.getColour() << " Player got home!!!!" << std::endl;
        return true;
    }

    removeCounterFromCurrentSpace(counter);

    // Set counters new newSpace
    space->setCounter(&counter);
    counter.setPosition(newPosition);

    return true;
}

void Game::removeCounterFromCurrentSpace(Counter& counter)
{
    int currentPosition = counter.getPosition();
    if(currentPosition > 56)
    {
        SpaceColour colour = counter.getColour();
        HomeRun& homeRun = m_home_runs[colour];
        Space* currentSpace = homeRun[currentPosition];
        assert(currentSpace->getCounter() == &counter);
        currentSpace->setCounter(nullptr);
    }
    else if(currentPosition >= 0)
    {
        Space* currentSpace = m_board[currentPosition];
        assert(currentSpace->getCounter() == &counter);
        currentSpace->setCounter(nullptr);
    }
}

bool Game::canAddNewCounter(int const &rollResult)
{
    return rollResult == 6 ? true : false;
}

int Game::rollDice()
{
    return 1 + std::rand()/((RAND_MAX + 1u)/6);
}
