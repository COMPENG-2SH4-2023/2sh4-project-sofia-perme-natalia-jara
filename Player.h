#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state

    Player(GameMechs *thisGMRef);
    ~Player();

    objPosArrayList *getPlayerPos();
    void updatePlayerDir();
    void movePlayer(Food *myFood);
    bool checkSnakeSuicide();

private:
    objPosArrayList *playerPosList;
    enum Dir myDir;

    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;

};

#endif