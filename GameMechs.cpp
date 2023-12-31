#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    loseFlag = 0;
    exitFlag = false;
    boardSizeX = 30; // default board size as recommended in manual
    boardSizeY = 15;
    foodNum = 5;     // number of food items to be generated
    featuresNum = 2; // num of special features
}

GameMechs::GameMechs(int boardX, int boardY, int numFood, int numFeatures)
{
    input = 0;
    score = 0;
    loseFlag = 0;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
    foodNum = numFood;
    featuresNum = numFeatures;
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar()) // check for unprocessed input character
    {
        input = MacUILib_getChar(); // store detected input character
    }

    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getFeaturesNum()
{
    return featuresNum;
}
int GameMechs::getFoodNum()
{
    return foodNum;
}

void GameMechs::setExitTrue()
{

    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

GameMechs::~GameMechs()
{
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore(char symbol) // depending on which symbol increase score by 1 or 5
{
    if (symbol == 'o')
    {
        score++;
    }
    else if (symbol == 'x')
    {
        score += 5;
    }
}

void GameMechs::decreaseScore() // decreases score by 1
{
    score--;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

bool GameMechs::setLoseFlag()
{
    loseFlag = true;
}