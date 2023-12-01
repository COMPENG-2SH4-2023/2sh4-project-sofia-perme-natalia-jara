#include "Food.h"
#include <time.h>
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

Food::Food(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList();
}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFoodBucket(objPosArrayList *blockOffList)
{
    foodBucket->clear();
    for (int i = 0; i < mainGameMechsRef->getFoodNum(); i++)
    {
        generateFood(blockOffList);
    }
}

void Food::generateFood(objPosArrayList *blockOffList)
{
    srand(time(NULL));

    int xVal;
    int yVal;
    int counter;
    objPos foodPos;

    while (true)
    {
        xVal = (rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1);

        if (!contains(blockOffList, xVal, yVal) && !contains(foodBucket, xVal, yVal))
        {
            foodPos.x = xVal;
            foodPos.y = yVal;
            foodPos.symbol = '*';
            foodBucket->insertTail(foodPos);
            break;
        }
    }
}

bool Food::contains(objPosArrayList *blockOffList, int x, int y)
{
    objPos listElement;
    if (blockOffList->getSize() == 0)
    {
        return false;
    }
    for (int i = 0; i < blockOffList->getSize(); i++)
    {
        blockOffList->getElement(listElement, i);

        if (x == listElement.x && y == listElement.y)
        {
            return true;
        }
    }
    return false;
}

objPosArrayList *Food::getFoodBucket()
{
    return foodBucket;
}