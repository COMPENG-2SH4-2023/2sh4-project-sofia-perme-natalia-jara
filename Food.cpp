#include "Food.h"
#include "MacUILib.h"
#include <stdlib.h>
#include <time.h>
#include "GameMechs.h"
#include "Player.h"
#include "objPos.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1, -1, 'o'); //initalize food outside gameboard
}

Food::~Food()
{

}

void Food::generateFood(objPosArrayList* blockOffList)
{

    srand(time(NULL));

    bool conflict = true;
    int xVal;
    int yVal;
    objPos playerTemp;

    while(conflict)
    {
        conflict = false; //initially no conflict in positions

        xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

        for(int i = 0; i < blockOffList->getSize(); i++) //checking each element of snake body
        {
            blockOffList->getElement(playerTemp, i); //get snake body element at for loop index

            if(xVal == playerTemp.x && yVal == playerTemp.y) //check if the pos is the same as blockOffList
            {
                conflict = true; 
                break;  
            }
        }
    }
    foodPos.x = xVal; //food position can be set once no conflict is detected
    foodPos.y = yVal;

}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos; //getter for food position (x and y coords)
}