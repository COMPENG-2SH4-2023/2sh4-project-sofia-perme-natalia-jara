#include "Food.h"
#include "MacUILib.h"
#include <time.h>
#include "GameMechs.h"
#include "Player.h"
#include "objPos.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1, -1, 'o');
}

Food::~Food()
{

}

void Food::generateFood(objPosArrayList* blockOffList)
{

    srand(time(NULL));

    bool drawn=true;
    int xVal;
    int yVal;
    objPos playerTemp;

    while(drawn)
    {
        drawn = false;

        xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

        for(int i = 0; i < blockOffList->getSize(); i++)
        {
            blockOffList->getElement(playerTemp, i);

            if(xVal == playerTemp.x && yVal == playerTemp.y)
            {
                drawn = true;
                break;
            }
        }
    }
    foodPos.x = xVal;
    foodPos.y = yVal;
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}