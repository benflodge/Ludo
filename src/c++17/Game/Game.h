#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <utility>
#include <assert.h>
#include "../HomeRun/HomeRun.h"
#include "../Player/Player.h"

class Board;
class Counter;
enum class SpaceType;
enum class SpaceColour;

enum class GameState {
    GAME_ROLL,
    GAME_MOVE,
    GAME_MENU,
    GAME_WON
};

class Game
{
    public:
        Game();
        void startGame(size_t players);
        Player* getPlayer(int i);
        Player* getPlayerForTurn();
        GameState getState();
        void rollDice();
        int getRollResult();
        int findNewCounterPosition(Counter& counter, int rollResult);
        bool moveCounter(Counter& counter, int newPosition);
        bool moveHomeRunCounter(Counter& counter, int newPosition);
        void turnOver();
        void removeCounterFromCurrentSpace(Counter& counter);
        static bool canAddNewCounter(int const &rollResult);

    private:
        GameState state;
        Board m_board;
        size_t playersTurn;
        int rollResult;
        std::vector<Player> m_players;
        std::map<SpaceColour, HomeRun> m_home_runs;
};