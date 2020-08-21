#pragma once
class Space;
enum class SpaceColour;

inline const int OFF_BOARD = -1;
inline const int HOME_POSITION = 62;

class Counter
{
    public:
		Counter(SpaceColour c);
		SpaceColour getColour();
		int getPosition();
		void setPosition(int position);
    private:
		SpaceColour m_colour;
		int m_position;
};
