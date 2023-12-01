#include "Food.h"
#include "MacUILib.h"
#include <stdlib.h>
#include <time.h>


Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1, -1, 'o'); //initalize food outside gameboard

    foodBucket = new objPosArrayList(); //memory storage for above and beyond
}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOffList)
{
    srand(time(NULL));
    int xVal;
    int yVal;
    objPos playerTemp;
    bool conflict=true;
    
    int i = 0;
    while(i < 2) //to generate first two special food objects
    {
        xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

        blockOffList->getElement(playerTemp, i); //get snake body element at for loop index

        if(xVal == playerTemp.x && yVal == playerTemp.y) //check if the pos is the same as blockOffList
        {
            continue;
        }
        for (int i=0; i<foodBucket->getSize();i++)   //check if pos is same as foodpos on board
        {
            if (xVal==foodPos.x && yVal==foodPos.y)
            {
                continue;
            }
        }

        foodPos.x = xVal; //food position can be set once no conflict is detected
        foodPos.y = yVal;
        foodPos.symbol = 'x';
        foodBucket->insertTail(foodPos);
        i++;
    }

    int j = 2;
    while(j < 5) //generating 3 elements (from 2-5) of regular food objects
    {
        xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

        blockOffList->getElement(playerTemp, j); //get snake body element at for loop index

        if(xVal == playerTemp.x && yVal == playerTemp.y) //check if the pos is the same as blockOffList
        {
            continue;
        }
        for (int j=2; i<foodBucket->getSize();i++) //check if pos is same as foodpos on board
        {
            if (xVal==foodPos.x && yVal==foodPos.y)
            {
                continue;
            }
        }

        foodPos.x = xVal; //food position can be set once no conflict is detected
        foodPos.y = yVal;
        foodPos.symbol = 'o';
        foodBucket->insertTail(foodPos);
        j++;
    }
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos; //getter for food position (x and y coords)
}

objPosArrayList* Food::getFoodBucket()
{
    return foodBucket;                   
}