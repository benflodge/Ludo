#pragma once
#include <memory>
#include <array>
#include "../Counter/Counter.h"

enum class SpaceColour;
inline const int COUNTERS = 4;

class Player
{
    public:
		Player(SpaceColour c);
		SpaceColour getColour();
		void setColour(SpaceColour colour);
		Counter* getCounter(int i);
    private:
		SpaceColour m_colour;
		std::array<Counter, COUNTERS> m_counters;
};

