#include "Player.h"
#include "MacUILib.h"
#include <iostream>

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'); 
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList *Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    switch (input)                                    //PPA2 input collection logic using (WASD input keys)
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
    mainGameMechsRef->clearInput(); // clear input buffer
}

void Player::movePlayer(Food *myFood)
{
    // PPA3 Finite State Machine logic

    objPos tempPos;
    objPos foodItem;

    objPos currHead; // holding pos info of current head
    playerPosList->getHeadElement(currHead);

    objPosArrayList *foodBucket = myFood->getFoodBucket();

    switch (myDir)                                         //PPA 2 movement logic
    {
    case UP:
        currHead.y--;
        if (currHead.y == 0) //PPA2 wraparound border logic
        {
            currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        break;

    case DOWN:
        currHead.y++;
        if (currHead.y == mainGameMechsRef->getBoardSizeY() - 1)
        {
            currHead.y = 1;
        }
        break;

    case LEFT:
        currHead.x--;
        if (currHead.x == 0)
        {
            currHead.x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        break;

    case RIGHT:
        currHead.x++;
        if (currHead.x == mainGameMechsRef->getBoardSizeX() - 1)    //PPA2 wraparound border logic
        {
            currHead.x = 1;
        }
        break;

    case STOP:
        break;
    }

    // if (currHead.x == mainGameMechsRef->getBoardSizeX() - 1)    //PPA2 wraparound border logic
    // {
    //     currHead.x = 1;
    // }
    // else if (currHead.x == 0)
    // {
    //     currHead.x = mainGameMechsRef->getBoardSizeX() - 2;
    // }
    // else if (currHead.y == 0)
    // {
    //     currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
    // }
    // else if (currHead.y == mainGameMechsRef->getBoardSizeY() - 1)
    // {
    //     currHead.y = 1;
    // }

    foodBucket->getByPos(foodItem,currHead.x,currHead.y);
    if (foodItem.symbol != '\0')                               //checks to make sure that the foodBucket item symbol is not null
    {
            switch (foodItem.symbol)
            {
                case 'o':                                       //normal case 'o' increases score and lenght by 1
                mainGameMechsRef->incrementScore('o');
                playerPosList->insertHead(currHead);
                break;
                case 'x':                                       //special case 'x' increase score by 5 without increasing size
                mainGameMechsRef->incrementScore('x');
                break;
                case 'p':                                        //special case 'p' decreases score by 1 and increases lenght by 1
                mainGameMechsRef->decreaseScore(); 
                playerPosList->insertHead(currHead);
            }
        
        myFood->generateFoodBucket(playerPosList);
    }
    else                                                         // if no collision detected
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
    }

    int size = playerPosList->getSize();            //check for snake self-suicide
    for (int i = 1; i < size; i++)
    {
        playerPosList->getElement(tempPos, i);
        if (currHead.x == tempPos.x && currHead.y == tempPos.y)    //if any of the snake body elements are equal to the head the set both exit and lose flags to true
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }
    }
}
