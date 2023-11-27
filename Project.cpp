#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

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
    // myPos.setObjPos(2,3,'@');

    myGM = new GameMechs(); // need to delete from heap?
    myPlayer = new Player(myGM);
    myFood = new Food();
    // exit flag removed because object myGM already has flag = false

    objPos playerPos;
    // objPos foodPos;
    // myPlayer->getPlayerPos();
    myFood->generateFood(playerPos);
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
    myPlayer->movePlayer();

    myGM->clearInput();

    myPlayer->getPlayerPos();
    myFood->getFoodPos(foodPos);

    if (playerPos.x == foodPos.x && playerPos.y == foodPos.y)
    {
        myFood->generateFood(playerPos);
        myGM->incrementScore();
    }

    // char set = myGM->getInput();

    // if(set == 'h' || set == 'H')
    // {
    //     objPos playerPos;
    //     objPos foodPos;
    //     myPlayer->getPlayerPos(playerPos);
    //     myFood->generateFood(playerPos);
    // }
}

void DrawScreen()
{
    MacUILib_clearScreen();

    objPosArrayList *playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    objPos foodPos;
    // myPlayer->getPlayerPos();
    // myFood->generateFood(playerPos);
    myFood->getFoodPos(foodPos);

    // MacUILib_printf("BoardSize: %dx%d,Player Pos: <%d, %d> + %c\n",
    //                 myGM->getBoardSizeX(),
    //                 myGM->getBoardSizeY(),
    //                 playerPos.x, playerPos.y, playerPos.symbol);

    int height = myGM->getBoardSizeY();
    int width = myGM->getBoardSizeX();
    int snakeSize = playerBody->getSize();
    bool drawn;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        drawn=false;
            for (int k = 0; k < snakeSize; k++)
            {
                playerBody->getElement(tempBody, k);
                if (j==tempBody.x  && i==tempBody.y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
                // if (drawn) continue;
            }

            
            
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            { // Use to check when reaching end/beginning of board in order to draw sides
                MacUILib_printf("#");
            }

            else if (i == foodPos.y && j == foodPos.x)
            {
                MacUILib_printf("%c", foodPos.symbol);
            }


            else
            {
                if (!drawn)
                {

                    MacUILib_printf("%c", ' '); // draw blanks in box
                }
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

    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
    delete myFood;
}
