#include "Player.h"
// #include "Food.h"
// #include "MacUILib.h"
#include <iostream>


Player::Player(GameMechs* thisGMRef,Food * thisFoodRef )
{
    mainGameMechsRef = thisGMRef;
    foodRef=thisFoodRef;
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


bool Player::checkFoodCollision(objPos tempPos)
{
    objPos foodPos;
    bool special;

    objPosArrayList * foodBucket = foodRef->getFoodBucket(); //giving seg fault
    MacUILib_printf("assigning foodBucket works in checkFoodCollision\n");

   

    for(int i = 0; i < foodBucket->getSize(); i++)   //problem with foodBucket and listSize -> returns segFault
    {

        if(foodPos.x == tempPos.x && foodPos.y == tempPos.y && foodPos.symbol == 'o')
        {
            special = false;
            break;

        }

        if(foodPos.x == tempPos.x && foodPos.y == tempPos.y && foodPos.symbol == '+')
        {
            special = true;
            break;
            // return true;
        }
    }
    return special;
    MacUILib_printf("for loop works in checkFoodCollision\n");
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

void Player::movePlayer(Food *myFood)
{
    // PPA3 Finite State Machine logic

    objPos tempPos;

    objPos currHead; // holding pos info of current head
    playerPosList->getHeadElement(currHead);

    objPos tempFood;
    myFood->getFoodPos(tempFood);

    switch (myDir)
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

    MacUILib_printf("movePlayer works before implementing collision logic\n");
    if (checkFoodCollision(tempPos) == false)
    {
        playerPosList->insertHead(tempPos);
        mainGameMechsRef->incrementScore(true);
        myFood->generateFood(playerPosList);
        MacUILib_printf("movePlayer works after implementing collision logic for special =true\n");
    }

    else if (checkFoodCollision(tempPos) == true)
    {
        playerPosList->insertHead(tempPos);
        playerPosList->removeTail();
        mainGameMechsRef->incrementScore(false);
        // myFood->generateFood(playerPosList);
        MacUILib_printf("movePlayer works after implementing collision logic for special =false\n");
    }

    else // if no collision detected
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
        MacUILib_printf("movePlayer works after implementing collision logic and there is no collision\n");
    }
}
void Player::checkSnakeSuicide()
{   
    objPos tempVar;
    objPos currentHead;   //holding pos info of current head
    playerPosList->getHeadElement(currentHead);
    int size = playerPosList->getSize();

    for (int i = 1; i < size; i++)
    {
        playerPosList->getElement(tempVar, i); // turn self collison into member function

        if (currentHead.x == tempVar.x && currentHead.y == tempVar.y) // if self collision detected
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            break;
        }
    }
}
