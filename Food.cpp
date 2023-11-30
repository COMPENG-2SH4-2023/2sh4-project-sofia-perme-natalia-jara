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

    //bool conflict = true;
    int xVal;
    int yVal;
    objPos playerTemp;
    int conflict=true;
    

    for(int i = 0; i < 2; i++) //checking each element of snake body
    {
        xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

        blockOffList->getElement(playerTemp, i); //get snake body element at for loop index

        if(xVal == playerTemp.x && yVal == playerTemp.y) //check if the pos is the same as blockOffList
        {
            continue;
        }

        foodPos.x = xVal; //food position can be set once no conflict is detected
        foodPos.y = yVal;
        foodPos.symbol = '+';
        foodBucket->insertTail(foodPos);
        MacUILib_printf("FoodBucket[%d]:%d,%d,%c\n",i,foodPos.x,foodPos.y,foodPos.symbol);
    }

    for(int i = 2; i < 5; i++) //checking each element of snake body
    {
        xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
        yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

        blockOffList->getElement(playerTemp, i); //get snake body element at for loop index

        if(xVal == playerTemp.x && yVal == playerTemp.y) //check if the pos is the same as blockOffList
        {
            continue;
        }

        foodPos.x = xVal; //food position can be set once no conflict is detected
        foodPos.y = yVal;
        foodPos.symbol = 'o';
        foodBucket->insertTail(foodPos);
        MacUILib_printf("FoodBucket[%d]:%d,%d,%c\n",i,foodPos.x,foodPos.y,foodPos.symbol);
    }
    

//     while(conflict)
//     {
//         conflict = false; //initially no conflict in positions

//         xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
//         yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

//         for(int i = 0; i < 2; i++) //checking each element of snake body
//         {
//             blockOffList->getElement(playerTemp, i); //get snake body element at for loop index

//             if(xVal == playerTemp.x && yVal == playerTemp.y) //check if the pos is the same as blockOffList
//             {
//                 conflict = true; 
//                 break;  
//             }
//         }
//     }
//     foodPos.x = xVal; //food position can be set once no conflict is detected
//     foodPos.y = yVal;
//     foodPos.symbol = '+';
//     foodBucket->insertHead(foodPos);
//     conflict=true;
//     MacUILib_printf("FoodBucket:%d,%d,%c\n",foodPos.x,foodPos.y,foodPos.symbol);

//     while(conflict)
//     {
//         conflict = false; //initially no conflict in positions

//         xVal = (rand() % (mainGameMechsRef->getBoardSizeX()-2) + 1);
//         yVal = (rand() % (mainGameMechsRef->getBoardSizeY()-2) + 1);

//         for(int i = 2; i < 5; i++) //checking each element of snake body
//         {
//             blockOffList->getElement(playerTemp, i); //get snake body element at for loop index

//             if(xVal == playerTemp.x && yVal == playerTemp.y) //check if the pos is the same as blockOffList
//             {
//                 conflict = true; 
//                 break;  
//             }
//         }
//     }
//     foodPos.x = xVal; //food position can be set once no conflict is detected
//     foodPos.y = yVal;
//     foodPos.symbol = 'o';
//     foodBucket->insertHead(foodPos);

}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos; //getter for food position (x and y coords)
}

objPosArrayList* Food::getFoodBucket()
{
    return foodBucket;
}