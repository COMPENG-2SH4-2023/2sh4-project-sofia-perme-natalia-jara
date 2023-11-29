#include "Food.h"
#include "MacUILib.h"
#include <time.h>
#include "GameMechs.h"
#include "Player.h"
#include "objPos.h"
#include "objPosArrayList.h"


Food::Food(GameMechs* thisGMRef,objPosArrayList* aFoodBucket)
{
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1, -1, 'o');
    foodBucket=aFoodBucket;
}

Food::~Food()
{

}

void Food::generateFood(objPosArrayList* blockOffList, bool special)
{
    srand(time(NULL));

    int xVal;
    int yVal;
    int counter;
    objPos playerTemp;

    while(true)
    {
        xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);
        
        if(!contains(blockOffList,xVal,yVal)&&!contains(foodBucket,xVal,yVal))
        {
            foodPos.x = xVal;
            foodPos.y = yVal;
            foodBucket->insertTail(foodPos);
            break;
        }
    }
}

bool Food::contains(objPosArrayList* blockOffList,int x,int y)
{
    objPos listElement;
    if (blockOffList->getSize()==0)
    {
        return false;
    }
    for(int i = 0; i < blockOffList->getSize(); i++)
        {
            blockOffList->getElement(listElement, i);

                if (x == listElement.x && y == listElement.y)
                {
                    return true;
                    
                }
        }
      return false;  

}


void Food::getFoodPos(objPos &returnPos)
{
    // returnPos.x = foodPos.x;
    // returnPos.y = foodPos.y;
    // returnPos.symbol = foodPos.symbol;

    //returnPos.setObjPos(foodPos.x,foodPos.y,foodPos.symbol);
    returnPos = foodPos;
}