#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // direction states

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // considers array list - now snake body
        void updatePlayerDir();
        void movePlayer(Food* myFood);

    private:
        objPosArrayList *playerPosList;      
        enum Dir myDir;
        GameMechs* mainGameMechsRef; // reference to Main Game Mechanics class
};

#endif