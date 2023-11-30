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

        // Player(GameMechs* thisGMRef);
        Player(GameMechs* thisGMRef,Food * thisFoodRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // considers array list - now snake body
        void updatePlayerDir();
        void movePlayer(Food* myFood);

        //bool checkSelfCollision(); //feature 3, iteration 3
        bool checkFoodCollision(objPos tempPos); //problem is we are creating new foodBucket from objPos not calling already filled one from food class
        void checkSnakeSuicide();

        // objPosArrayList*setFoodBucket(Food * myFood,objPosArrayList* foodBucket);



    private:
        objPosArrayList *playerPosList;
        // objPosArrayList * foodBucket;      
        enum Dir myDir;
        GameMechs* mainGameMechsRef; // reference to Main Game Mechanics class
        Food* foodRef;  //refrence to food class

};

#endif