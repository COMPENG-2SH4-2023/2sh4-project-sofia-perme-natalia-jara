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

    objPos currHead;   //holdingh pos info of current head
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
            //currHead.y--;
            break;

        case DOWN:
            currHead.y++;
            if (currHead.y==mainGameMechsRef->getBoardSizeY()-1)
            {
                currHead.y=1;
            }
            //currHead.y++;
            break;

        case LEFT:
            currHead.x--;
            if (currHead.x==0)
            {
                currHead.x=mainGameMechsRef->getBoardSizeX()-2;
            }
            //currHead.x--;
            break;

        case RIGHT:
            currHead.x++;
            if (currHead.x==mainGameMechsRef->getBoardSizeX()-1)
            {
                currHead.x=1;
            }
            //currHead.x++;
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

    if(tempFood.x == currHead.x && tempFood.y == currHead.y) //if food and player collision detected
    {
        playerPosList->insertHead(currHead);
        mainGameMechsRef->incrementScore();
        myFood->generateFood(playerPosList);
    }

    else //if no collision detected
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
    }

    int size=playerPosList->getSize();
    
    for (int i=1;i<size;i++)
    {
        playerPosList->getElement(tempPos,i);

        if(currHead.x==tempPos.x && currHead.y==tempPos.y) //if self collision detected
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }

    }
 
}
