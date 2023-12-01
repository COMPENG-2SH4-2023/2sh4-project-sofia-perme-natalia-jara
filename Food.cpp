#include "Food.h"
#include <time.h>
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"


Food::Food(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList();
}

Food::~Food()
{
    delete foodBucket;
}

int Food::generateFoodBucket(objPosArrayList *blockOffList)
{
    int counter = 0;
    foodBucket->clear();
    int regularFeaturesNum = mainGameMechsRef->getFoodNum() - mainGameMechsRef->getFeaturesNum();
    for (int i = 0; i < regularFeaturesNum; i++)
    {
        generateFood(blockOffList, false);
    }
    for (int i = 0; i < mainGameMechsRef->getFeaturesNum(); i++)
    {
        generateFood(blockOffList, true);
    }
    return counter;
}

bool Food::generateFood(objPosArrayList *blockOffList, bool special)
{
    srand(time(NULL));

    int xVal;
    int yVal;
    int counter;
    int randNum;
    objPos foodPos;

    while (true)
    {
        xVal = (rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1);

        if (!contains(blockOffList, xVal, yVal) && !contains(foodBucket, xVal, yVal))
        {
            foodPos.symbol = generateSymbol(special);
            foodPos.x = xVal;
            foodPos.y = yVal;
            foodBucket->insertTail(foodPos);
            break;
        }
    }
}

char Food::generateSymbol(bool special) // generates symbol using rand() function
{
    if (!special)
    {
        return 'o';
    }
    int randNum;
    char symbol;
    randNum = (rand() % 2);
    switch (randNum)
    {
    case 0:
        symbol = 'x';
        break;
    case 1:
        symbol = 'p';
        break;
    }
    return symbol;
}

bool Food::checkFoodBucket()
{
    int counter = 0;
    objPos foodItem;
    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        foodBucket->getElement(foodItem, i);
        if (foodItem.symbol == 'o')
        {
            counter++;
        }
    }
    if (counter == 2)
    {
        return true;
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