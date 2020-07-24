#pragma once
class Space;
enum class SpaceColour;

class Counter
{
    public:
		Counter(SpaceColour c);
		SpaceColour getColour();
		Space& getSpace();
		void setSpace(Space* space);
    private:
		SpaceColour m_colour;
		Space *m_space;
};
