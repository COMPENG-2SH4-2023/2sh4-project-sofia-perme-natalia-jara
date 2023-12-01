#include "GameMechs.h"
// #include "MacUILib.h"
//#include "Food.h"

GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    loseFlag = false;
    exitFlag = false;
    boardSizeX = 30; //default board size as recommended in manual
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    loseFlag = false;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar()) //check for unprocessed input character
    {
        input = MacUILib_getChar(); //store detected input character
    }

    return input;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore(char symbol)
{
    if(symbol == 'x')             //if special character increment score by 5
    {
        score += 5;
    }

    else                         //else if regular increment by 1
    {
        score += 1;
    }
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

bool GameMechs::setLoseFlag()
{
    loseFlag = true;
}
