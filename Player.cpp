#include "Player.h"
#include "Food.h"
#include "MacUILib.h"
#include <iostream>


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,mainGameMechsRef->getBoardSizeY() / 2, '@');     //possible to write in simpler way--research way

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

}

Player::~Player()
{
    delete playerPosList; //do not need a square breacket since we only have one
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

int Player::checkFoodCollision(objPos tempPos, objPosArrayList* foodBucket)
{
    objPos foodPos;
    bool special;

    for(int i = 0; i < foodBucket->getSize(); i++)
    {
        foodBucket->getElement(foodPos,i);

        if(foodPos.x == tempPos.x && foodPos.y == tempPos.y && foodPos.symbol == 'o')
        {
            special = false;
            break;
        }

        if(foodPos.x == tempPos.x && foodPos.y == tempPos.y && foodPos.symbol == '+')
        {
            special = true;
            break;
        }
    }
    return special;
}


void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case ' ':
            mainGameMechsRef->setExitTrue();   
            break;
        case 'w': // up
        case 'W':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;

        case 's': // down
        case 'S':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;

        case 'a': // left
        case 'A':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        case 'd': // right
        case 'D':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;

    }  

    mainGameMechsRef->clearInput(); //clear input buffer
}

void Player::movePlayer(Food* myFood)
{
    // PPA3 Finite State Machine logic

    objPos tempPos;

    objPos currHead;   //holding pos info of current head
    playerPosList->getHeadElement(currHead);
    

    objPos tempFood;
    myFood->getFoodPos(tempFood);

     switch (myDir)
    {
        case UP:
            currHead.y--;
            if (currHead.y==0)
            {
                currHead.y=mainGameMechsRef->getBoardSizeY()-2;
            }
            break;

        case DOWN:
            currHead.y++;
            if (currHead.y==mainGameMechsRef->getBoardSizeY()-1)
            {
                currHead.y=1;
            }
            break;

        case LEFT:
            currHead.x--;
            if (currHead.x==0)
            {
                currHead.x=mainGameMechsRef->getBoardSizeX()-2;
            }
            break;

        case RIGHT:
            currHead.x++;
            if (currHead.x==mainGameMechsRef->getBoardSizeX()-1)
            {
                currHead.x=1;
            }
            break;

        case STOP:
            break;
    }

    // if (currHead.x==mainGameMechsRef->getBoardSizeX()-1)
    // {
    //     currHead.x=1;
    // }
    // else if (currHead.x==0)
    // {
    //     currHead.x=mainGameMechsRef->getBoardSizeX()-2;
    // }
    // else if (currHead.y==0)
    // {
    //     currHead.y=mainGameMechsRef->getBoardSizeY()-2;
    // }
    // else if (currHead.y==mainGameMechsRef->getBoardSizeY()-1)
    // {
    //     currHead.y=1;
    // }

    // if(tempFood.x == currHead.x && tempFood.y == currHead.y) //if food and player collision detected
    // {
    //     playerPosList->insertHead(currHead);
    //     mainGameMechsRef->incrementScore();
    //     myFood->generateFood(playerPosList);
    // }

    if(checkFoodCollision(tempPos, foodBucket) == false)
    {
        playerPosList->insertHead(tempPos);
        mainGameMechsRef->incrementScore();
        myFood->generateFood(playerPosList);
    }

    else if(checkFoodCollision(tempPos, foodBucket) == true)
    {
        playerPosList->insertHead(tempPos);
        playerPosList->removeTail();
        mainGameMechsRef->incrementScore();
        // myFood->generateFood(playerPosList);
    }

    else //if no collision detected
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
    }

    int size=playerPosList->getSize();
    
    for (int i=1;i<size;i++)
    {
        playerPosList->getElement(tempPos,i); //turn self collison into member function

        if(currHead.x==tempPos.x && currHead.y==tempPos.y) //if self collision detected
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }

    }
 
}
