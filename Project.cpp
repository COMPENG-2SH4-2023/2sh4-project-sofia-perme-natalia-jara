#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include <time.h>


#define DELAY_CONST 100000 

#define FOOD_NUM 5
#define FEATURES_NUM 2


GameMechs* myGM; //should i be using destructor function to remove from heap or just delete call?
Player* myPlayer;//should i move these heap variables into their respective classes?
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

    myGM = new GameMechs(30,15,FOOD_NUM,FEATURES_NUM); // need to delete from heap?
    myPlayer = new Player(myGM);
    myFood = new Food(myGM);
    myFood->generateFoodBucket(myPlayer->getPlayerPos());

 }

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void) 
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer(myFood);

    myGM->clearInput();

    myPlayer->getPlayerPos();

}

void DrawScreen()
{
    MacUILib_clearScreen();

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPosArrayList* foodBucket = myFood->getFoodBucket();

    int height = myGM->getBoardSizeY();
    int width = myGM->getBoardSizeX();
    int snakeSize = playerBody->getSize();
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            objPos playerPos;
            playerBody->getByPos(playerPos,j,i);
            objPos foodPos;
            myFood->getFoodBucket()->getByPos(foodPos,j,i);
  
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            { // Use to check when reaching end/beginning of board in order to draw sides
                MacUILib_printf("%s","#");
            }
            else if(playerPos.symbol!='\0')
            {
                MacUILib_printf("%c",playerPos.symbol);
            }
            else if(foodPos.symbol!='\0')
            {
                MacUILib_printf("%c",foodPos.symbol);
            }
            else
            {
                MacUILib_printf("%c",' ');
            }
        }
        MacUILib_printf("%s", "\n");
    }
    MacUILib_printf("Welcome to SNAKE GAME! Press space bar to exit.");
    MacUILib_printf("\nScore: %d", myGM->getScore());
    //MacUILib_printf("\nLose flag: %d", myGM->getLoseFlagStatus());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    // MacUILib_clearScreen();
    if (myGM->getLoseFlagStatus()==false && myGM->getExitFlagStatus() == true)
    {
        MacUILib_printf("%s", "\n");
        MacUILib_printf("\nEXIT GAME.");
        MacUILib_printf("\nYOUR FINAL SCORE: %d", myGM->getScore());
        MacUILib_uninit();
    }
     if (myGM->getLoseFlagStatus()==true)
     {
        MacUILib_printf("%s", "\n");
        MacUILib_printf("\nSNAKE RAN INTO ITSELF... YOU LOSE :(");
        MacUILib_printf("\nYOUR FINAL SCORE: %d", myGM->getScore());
        MacUILib_uninit();
     }

    delete myGM;
    delete myPlayer;
    delete myFood;
}
