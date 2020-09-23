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

Game::Game() : state{ GameState::GAME_MENU }, playersTurn{ 0 }, rollResult{ 0 } {};

void Game::startGame(size_t players)
{   
    assert(state == GameState::GAME_MENU);

    for (size_t i = 0; i < players; i++)
    {
        SpaceColour colour = static_cast<SpaceColour>(i);
        m_players.push_back(Player(colour));
        m_home_runs.emplace(colour, HomeRun(colour));
    }

    state = GameState::GAME_ROLL;
}

Player* Game::getPlayer(int i)
{
    return &m_players[i];
}

Player* Game::getPlayerForTurn()
{
    return &m_players[playersTurn];
}

GameState Game::getState()
{
    return state;
};

void Game::rollDice()
{
    rollResult = 1 + std::rand() / ((RAND_MAX + 1u) / 6);
    state = GameState::GAME_MOVE;
}

int Game::getRollResult()
{
    return rollResult;
}

// Returns the counters new position depending on the dice roll.
// The Board spaces start at 0 and go to 55. 
// Each players starting space is spaced evenly at 14 space intervals starting at 0.
// The players end space is the space before their starting space.
// A player can only add a new counter to the board if they roll a 6.
// If the counter is on the board, the dice roll is added to the position.
// When a player gets to space 55 the next move should wrap them back to and past 0.
// If a counter cannot move the current position is returned.
// If a counter's new position is past it's end space, the can move onto the home run.
// The home run starts at 56 and ends at 61, the end space.
int Game::findNewCounterPosition(Counter& counter, int rollResult)
{
    bool canAddNew = Game::canAddNewCounter(rollResult);
    int counterPos = counter.getPosition();
    SpaceColour playerColour = counter.getColour();
    int startPosition = m_board.getStart(playerColour);
    int endPosition = startPosition == 0 ? BOARD_SIZE - 1 : startPosition - 1;
    int newPosition = counterPos;

    if(counterPos == OFF_BOARD && canAddNew)
    {
        // If the player rolls 6 they may put a counter onto the board, at their start space
        newPosition = startPosition;
    }
    else if (counterPos != OFF_BOARD)
    {
        newPosition = counterPos + rollResult;
        if (counterPos < BOARD_SIZE && newPosition >= BOARD_SIZE && endPosition != BOARD_SIZE - 1)
        {
            // wrap the position round (55 back to 0), but not for the first player, let them onto the home run.
            newPosition = newPosition % (BOARD_SIZE - 1);
        }
    }
    
    if(counterPos != OFF_BOARD && counterPos <= endPosition && newPosition > endPosition)
    // Roll __ Current <= end    &&  new > end
    // 6s   __ -1 <= 55 == true  &&  0 > 55 == false 
    // 6   __ 0 <= 55   == true  &&  6 > 55 == false 
    // 3    __ 55 <= 55 == true  &&  58 > 55 == true
    // 3    __ 55 <= 55 == true  &&  2 > 55 == false
    // 6s   __ -1 <= 13 == true  &&  14 > 13 == true // fixed with counterPos != OFF_BOARD
    // 3   __ 14 <= 13  == false &&  17 > 13 == true
    // 3   __ 55 <= 13  == false &&  2 > 13 == false 
    // 4   __ 2 <= 13   == true  &&  6 > 13 == false 
    // 4   __ 12 <= 13  == true  &&  16 > 13 == true 
    // 4   __ 12 <= 13  == true  &&  16 > 13 == true 
    // 6   __ 10 <= 13  == true  && 16 > 13 == true
    {
        // Move the counter to the home run 56 - 61
        newPosition = BOARD_SIZE - 1 + (newPosition - endPosition);
        assert(newPosition >= BOARD_SIZE);
        assert(newPosition < BOARD_SIZE + HOME_RUN_SIZE);
    }

    return newPosition;
}

bool Game::moveCounter(Counter& counter, int newPosition)
{
    Space* newSpace = m_board[newPosition];
    Counter* target = newSpace->getCounter();

    if(target && target->getColour() == counter.getColour())
    {
        // Cannot move on top of another counter of the same colour
        return false;
    }
    else if (target)
    {
        // Send another players counter off the board 
        std::cout << (int)counter.getColour() << " Player took: " << (int)target->getColour() << std::endl;
        target->setPosition(OFF_BOARD);
        removeCounterFromCurrentSpace(*target);
    }

    removeCounterFromCurrentSpace(counter);

    // Set counters new newSpace
    newSpace->setCounter(&counter);
    counter.setPosition(newPosition);

    turnOver();
    return true;
}

bool Game::moveHomeRunCounter(Counter& counter, int newPosition)
{
    int newHomeRunPosition = newPosition - BOARD_SIZE;

    if (newHomeRunPosition >= HOME_RUN_SIZE)
    {
        // Need exact number to end the game
        return false;
    }

    SpaceColour colour = counter.getColour();
    HomeRun& homeRun = m_home_runs[colour];

    Space* space = homeRun[newHomeRunPosition];
    Counter* target = space->getCounter();

    if(target)
    {
        // Cannot move on top of another counter of the same colour
        return false;
    }

    if (newPosition == HOME_POSITION)
    {
        std::cout << (int)counter.getColour() << " Player got home!!!!" << std::endl;
    }
    else 
    {
        // Set counters new newSpace
        space->setCounter(&counter);
    }

    removeCounterFromCurrentSpace(counter);
    counter.setPosition(newPosition);

    turnOver();
    return true;
}

void Game::turnOver()
{
    bool hasWon = true;
    Player* player = getPlayerForTurn();

    for (size_t k = 0; k < COUNTERS; k++)
    {
        Counter* counter = player->getCounter(k);
        if (counter->getPosition() != HOME_POSITION)
        {
            hasWon = false;
        }
    }

    if (hasWon)
    {
        state = GameState::GAME_WON;
    }
    else
    {
        playersTurn = playersTurn < m_players.size() - 1 ? (playersTurn + 1) : 0;
        state = GameState::GAME_ROLL;
    }
}

void Game::removeCounterFromCurrentSpace(Counter& counter)
{
    int currentPosition = counter.getPosition();
    if(currentPosition >= BOARD_SIZE)
    {
        int homeRunPosition = currentPosition - BOARD_SIZE;
        SpaceColour colour = counter.getColour();
        HomeRun& homeRun = m_home_runs[colour];
        Space* currentSpace = homeRun[homeRunPosition];
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


