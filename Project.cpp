#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include <time.h>

using namespace std;

// #define DELAY_CONST 100000 
#define DELAY_CONST 100000 //fix this

//Global scope - as done and allowed in tutorial
GameMechs* myGM; 
Player* myPlayer;
Food* myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

objPos myPos;

int main(void)
{

    Initialize();

    while (myGM->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(30,15); //set board size using additional constructor
    myFood = new Food(myGM); //for food generation
    myPlayer = new Player(myGM,myFood);

    objPos playerPos;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myFood->generateFood(playerBody);
}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    objPos playerPos;
    objPos foodPos;

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(myFood);
    

    myPlayer->getPlayerPos();
    myFood->getFoodPos(foodPos);

    myGM->clearInput(); //so input is not repeatedly processed

}

void DrawScreen()
{
    MacUILib_clearScreen();

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPosArrayList* foodBucket = myFood->getFoodBucket();

    objPos tempBody;

    objPos foodPos;
    myFood->getFoodPos(foodPos);

    int height = myGM->getBoardSizeY();
    int width = myGM->getBoardSizeX();
    int snakeSize = playerBody->getSize();
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bool printSnake = false;

            for (int k = 0; k < snakeSize; k++)
            {
                playerBody->getElement(tempBody, k);

                if (j == tempBody.x  && i == tempBody.y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    printSnake = true;
                    break;
                }
            
            }

            if(printSnake)
            {
                continue;
            }  

            bool printFood = false;

            for(int k = 0; k < foodBucket->getSize(); k++)
            {
                foodBucket->getElement(foodPos, k);

                if(i == foodPos.y && j == foodPos.x)
                {
                    MacUILib_printf("%c", foodPos.symbol);
                    printFood = true;
                    break;
                }

            }

            if(printFood)
            {
                continue;
            }
            
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            { // Use to check when reaching end/beginning of board in order to draw sides
                MacUILib_printf("%s","#");
            }



            else
            {
                MacUILib_printf("%s"," ");
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d", myGM->getScore());
    MacUILib_printf("\nLose flag: %d", myGM->getLoseFlagStatus());
    MacUILib_printf("\nFood Pos: <%d, %d>, + %c\n", foodPos.x, foodPos.y, foodPos.symbol);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    // MacUILib_clearScreen();

    if (myGM->getLoseFlagStatus()==false && myGM->getExitFlagStatus()==true)
    {
        MacUILib_printf("\nEXIT GAME.");
    }

    if (myGM->getLoseFlagStatus()==true)
    {
        MacUILib_printf("\nSNAKE RAN INTO ITSELF... YOU LOSE :(");
    }

    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
    delete myFood;
}
