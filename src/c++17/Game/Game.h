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

class Game
{
    public:
        Game();
        Game(size_t players);
        Player* getPlayer(int i);
        int findNewCounterPosition(Counter& counter, SpaceColour playerColour, int rollResult);
        bool moveCounter(Counter& counter, int newPosition);
        bool moveHomeRunCounter(Counter& counter, int newPosition);
        void removeCounterFromCurrentSpace(Counter& counter);
        static bool canAddNewCounter(int const &rollResult);
        static int rollDice();

    private:
        Board m_board;
        std::vector<Player> m_players;
        std::map<SpaceColour, HomeRun> m_home_runs;
};