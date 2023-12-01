#include "Player.h"
// #include "Food.h"
// #include "MacUILib.h"
#include <iostream>

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'); 
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    delete playerPosList; // do not need a square breacket since we only have one
}

objPosArrayList *Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

char Player::checkFoodCollision(objPos tempPos)
{
    objPos foodPos;
    objPosArrayList *foodBucket = foodRef->getFoodBucket(); // getting and filling empty objArrayList with foodBucket list

    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        foodBucket->getElement(foodPos, i);

        if (foodPos.x == tempPos.x && foodPos.y == tempPos.y)      //clearing foodBucket to allow it to be empty for when its re generated again later
        {
            foodBucket->removeTail();                              //remove tails is emptying elements in foodBucket
            foodBucket->removeTail();
            foodBucket->removeTail();
            foodBucket->removeTail();
            foodBucket->removeTail();

            return foodPos.symbol;
        }
    }

    return 'n';
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    char input = mainGameMechsRef->getInput();

    switch (input)   
    {                                      //PPA 2 logic to change direction of player using input key (uses WASD keys)
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

    objPos currHead; // holding pos info of current head
    playerPosList->getHeadElement(currHead);

    switch (myDir)                                        //wraparound logic and player movement logic from PPA2                     
    {
    case UP:
        currHead.y--;                               
        if (currHead.y == 0)
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
        if (currHead.x == mainGameMechsRef->getBoardSizeX() - 1)
        {
            currHead.x = 1;
        }
        break;

    case STOP:
        break;
    }

    if (checkSnakeSuicide())                      // if snake body has self collision (true) set lose abnd exit flags to exit game by losing
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
    char sym = checkFoodCollision(currHead);

    if (sym == 'o')                             //regular food collision increments score by 1 and increase lenght by 1
    {
        playerPosList->insertHead(currHead);
        mainGameMechsRef->incrementScore('o');
        myFood->generateFood(playerPosList);
        return;
    }

    else if (sym == 'x')                       //increment score by 5 if special food item x collides with head
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
        mainGameMechsRef->incrementScore('x');
        myFood->generateFood(playerPosList);
        return;
    }
        // if no collision detected
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
}
bool Player::checkSnakeSuicide()    
{
    objPos snakeBody;
    objPos currentHead; // holding pos info of current head
    playerPosList->getHeadElement(currentHead);
    int size = playerPosList->getSize();

    for (int i = 1; i < size; i++)
    {
        playerPosList->getElement(snakeBody, i); // turn self collison into member function

        if (currentHead.x == snakeBody.x && currentHead.y == snakeBody.y) // if self collision detected
        {
            return true;
        }
    }

    return false;
}
