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

    bool drawn;
    int xVal;
    int yVal;
    objPos playerTemp;

    while(true)
    {
        drawn = false;

        xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

        // MacUILib_printf("x val is %d, ", xVal);
        // MacUILib_printf("y val is %d\n", yVal);

        for(int i = 0; i < blockOffList->getSize(); i++)
        {
            blockOffList->getElement(playerTemp, i);

            if(xVal != playerTemp.x && yVal != playerTemp.y)
            {
                foodPos.x = xVal;
                foodPos.y = yVal;
                drawn = true;
                break;
            }
        }

        if(drawn)
        {
            break; //break out of while loop when valid food pos is found
        }


    }

}

// void Food::regenerateFood()
// {
//     char input = mainGameMechsRef->getInput();

//     switch(input)
//     {
//         case 'h':
//             generateFood(foodPos);
//             break;
//     }
//     mainGameMechsRef->clearInput();
// }

void Food::getFoodPos(objPos &returnPos)
{
    // returnPos.x = foodPos.x;
    // returnPos.y = foodPos.y;
    // returnPos.symbol = foodPos.symbol;

    //returnPos.setObjPos(foodPos.x,foodPos.y,foodPos.symbol);
    returnPos = foodPos;
}