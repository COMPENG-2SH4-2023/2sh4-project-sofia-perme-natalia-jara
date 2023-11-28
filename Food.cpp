#include "Food.h"
#include "MacUILib.h"
#include <time.h>

Food::Food()
{
    //mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1, -1, 'o');
}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{

    srand(time(NULL));

    int xVal;
    int yVal;
    int size;

    while(true)
    {
        // size=playerPosList->getSize();


        xVal = rand() % (30-2) + 1;
        yVal = rand() % (15-2) + 1;

        MacUILib_printf("x val is %d, ", xVal);
        MacUILib_printf("y val is %d\n", yVal);


        if(xVal != blockOff.x && yVal != blockOff.y)
        {
            foodPos.x = xVal;
            foodPos.y = yVal;
            break;
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

    returnPos.setObjPos(foodPos.x,foodPos.y,foodPos.symbol);
}