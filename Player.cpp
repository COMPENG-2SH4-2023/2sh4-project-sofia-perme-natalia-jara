#include "Player.h"
#include "MacUILib.h"
#include <iostream>

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@'); // possible to write in simpler way--research way

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
    switch (input)
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

    objPos currHead; // holdingh pos info of current head
    playerPosList->getHeadElement(currHead);

    objPosArrayList *foodBucket = myFood->getFoodBucket();

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

    if (currHead.x == mainGameMechsRef->getBoardSizeX() - 1)
    {
        currHead.x = 1;
    }
    else if (currHead.x == 0)
    {
        currHead.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (currHead.y == 0)
    {
        currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (currHead.y == mainGameMechsRef->getBoardSizeY() - 1)
    {
        currHead.y = 1;
    }

    foodBucket->getByPos(foodItem,currHead.x,currHead.y);
    if (foodItem.symbol != '\0')
    {
            switch (foodItem.symbol)
            {
                case 'o':                                       //normal case 'o'
                mainGameMechsRef->incrementScore();
                break;
                case 'x':                                       //case 'x' increase score by 3 without increasing size
                mainGameMechsRef->incrementScore();
                mainGameMechsRef->incrementScore();
                mainGameMechsRef->incrementScore();
                break;
                case 'p':                                        //case 'p' decrease score by 1
                mainGameMechsRef->decreaseScore(); 
            }
        playerPosList->insertHead(currHead);
        myFood->generateFoodBucket(playerPosList);
    }
    else // if no collision detected
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
    }

    int size = playerPosList->getSize();
    for (int i = 1; i < size; i++)
    {
        playerPosList->getElement(tempPos, i);
        if (currHead.x == tempPos.x && currHead.y == tempPos.y)
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }
    }
}
