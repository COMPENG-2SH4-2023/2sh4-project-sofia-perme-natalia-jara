#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,
                        mainGameMechsRef->getBoardSizeY() / 2,
                        '@');

    //no heap player yet; no new yet
}


Player::~Player()
{
    // delete any heap members here
    //can leave empty for now
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x,playerPos.y,playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    //Where do I get the input where do I check for input
    //input-not by calling get char 
    // coordinate with teammemeber whos desining game mechanism
    char input = mainGameMechsRef->getInput();
    switch(input)
    {
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
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

