#include "Player.h"
#include "Food.h"
#include "MacUILib.h"
#include <iostream>


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;

    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,mainGameMechsRef->getBoardSizeY() / 2, '@');     //possible to write in simpler way--research way

    playerPosList=new objPosArrayList();

    playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    //no heap player yet; no new yet
}


Player::~Player()
{
    // delete any heap members here
    //can leave empty for now
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

    //Where do I get the input where do I check for input
    //input-not by calling get char 
    // coordinate with teammemeber whos desining game mechanism
    // objPos myPos;
    //GameMechs* myGM;
    char input = mainGameMechsRef->getInput();
    // bool setExitTrue=mainGameMechsRef->setExitTrue();
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
        // case 'p':
        // case 'P':
        //     mainGameMechsRef->incrementScore();
        //     break;

        case 'k':
        case 'K':
            mainGameMechsRef->setLoseFlag();
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
        break;
    case DOWN:
        currHead.y++;
        break;
    case LEFT:
        currHead.x--;
        break;
    case RIGHT:
        currHead.x++;
        break;
    case STOP:
        break;
    }

    if (currHead.x==mainGameMechsRef->getBoardSizeX()-1)
    {
        currHead.x=1;
    }
    else if (currHead.x==0)
    {
        currHead.x=mainGameMechsRef->getBoardSizeX()-2;
    }
    else if (currHead.y==0)
    {
        currHead.y=mainGameMechsRef->getBoardSizeY()-2;
    }
    else if (currHead.y==mainGameMechsRef->getBoardSizeY()-1)
    {
        currHead.y=1;
    }
    if(tempFood.x == currHead.x && tempFood.y == currHead.y)
    {
        myFood->generateFood(playerPosList);
        playerPosList->insertHead(currHead);
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
        playerPosList->getElement(tempPos,i);
        if(currHead.x==tempPos.x && currHead.y==tempPos.y)
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }

    }



    

    //new current head should be insertedto the head of the list
    // playerPosList->insertHead(currHead);
    // then remove tail
    // playerPosList->removeTail();
}
