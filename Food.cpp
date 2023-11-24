#include "Food.h"
#include "MacUILib.h"
#include <time.h>

Food::Food()
{
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

    while(true)
    {
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

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.x = foodPos.x;
    returnPos.y = foodPos.y;
    returnPos.symbol = foodPos.symbol;
}