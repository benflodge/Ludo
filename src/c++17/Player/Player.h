#pragma once
#include <memory>
#include <array>

class Counter;
enum class SpaceColour;

class Player
{
    public:
		Player(SpaceColour c);
		SpaceColour getColour();
		void setColour(SpaceColour colour);
    private:
		SpaceColour m_colour;
		std::array<std::shared_ptr<Counter>, 4> m_counters;
};

