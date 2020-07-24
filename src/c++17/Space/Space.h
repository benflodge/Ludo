#pragma once
class Counter;
enum class SpaceType;
enum class SpaceColour;

class Space
{
    public:
        Space();
        Space(SpaceColour c, SpaceType t);
        SpaceType getType();
        SpaceColour getColour();
        Counter &getCounter();
        void setCounter(Counter* counter);
    private:
        SpaceType m_type;
        SpaceColour m_colour;
        Counter *m_counter;
};
