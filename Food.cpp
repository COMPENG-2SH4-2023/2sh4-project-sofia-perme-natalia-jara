#include "Food.h"
#include "MacUILib.h"

Food::Food()
{
    foodPos = objPos();
    foodPos.x = 0;
    foodPos.y = 0;
    foodPos.symbol = '0';
}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{
    int xVal;
    int yVal;

    while(true)
    {
        xVal = rand() % 28 + 1;
        yVal = rand() % 13 + 1;

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