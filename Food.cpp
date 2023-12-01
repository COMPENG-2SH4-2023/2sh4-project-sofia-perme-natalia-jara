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
    int regularFeaturesNum = mainGameMechsRef->getFoodNum() - mainGameMechsRef->getFeaturesNum(); // subtracting number of regular 'o' food items by special items
    for (int i = 0; i < regularFeaturesNum; i++)                                                  // generating regular food items
    {
        generateFood(blockOffList, false);
    }
    for (int i = 0; i < mainGameMechsRef->getFeaturesNum(); i++) // generating special features
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

        if (!contains(blockOffList, xVal, yVal) && !contains(foodBucket, xVal, yVal)) // check if it has same pos as blockOffList and foodBucket items on board
        {
            foodPos.symbol = generateSymbol(special);
            foodPos.x = xVal;
            foodPos.y = yVal;
            foodBucket->insertTail(foodPos);
            break;
        }
    }
}

char Food::generateSymbol(bool special) // generates symbol using rand() function and
// accepts a bool that tell the generate symbol function to either generate a regular or special food item
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

bool Food::contains(objPosArrayList *blockOffList, int x, int y)
{
    objPos listElement;
    if (blockOffList->getSize() == 0) // checking to make sure that its not null
    {
        return false;
    }
    for (int i = 0; i < blockOffList->getSize(); i++)
    {
        blockOffList->getElement(listElement, i); // checking each individual element

        if (x == listElement.x && y == listElement.y) // check if x and y equal snake position coordinates
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