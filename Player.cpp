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
        case 'p':
        case 'P':
            mainGameMechsRef->incrementScore();
            break;

        case 'k':
        case 'K':
            mainGameMechsRef->setLoseFlag();
            break;
    }  

    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic


     switch (myDir)
    {
    case UP:
        playerPos.y--;
        break;
    case DOWN:
        playerPos.y++;
        break;
    case LEFT:
        playerPos.x--;
        break;
    case RIGHT:
        playerPos.x++;
        break;
    case STOP:
        break;
    }

    if (playerPos.x==mainGameMechsRef->getBoardSizeX()-1)
    {
        playerPos.x=1;
    }
    else if (playerPos.x==0)
    {
        playerPos.x=mainGameMechsRef->getBoardSizeX()-2;
    }
    else if (playerPos.y==0)
    {
        playerPos.y=mainGameMechsRef->getBoardSizeY()-2;
    }
    else if (playerPos.y==mainGameMechsRef->getBoardSizeY()-1)
    {
        playerPos.y=1;
    }

}

