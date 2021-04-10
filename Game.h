// Game.h
#include "Arena.h"
#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.
class Arena;

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
private:
    Arena* m_arena;
};

#endif // GAME_INCLUDED
