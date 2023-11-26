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
Player* myPlayer; //should i move these heap variables into their respective classes?
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

    while(myGM->getExitFlagStatus() == false) 
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

    myGM = new GameMechs(); //need to delete from heap?
    myPlayer = new Player(myGM);
    myFood = new Food();
    //exit flag removed because object myGM already has flag = false

    objPos playerPos;

    myPlayer->getPlayerPos(playerPos);
    myFood->generateFood(playerPos);

}

void GetInput(void)
{
    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    //myFood->regenerateFood();

    //myGM->clearInput();


}

void DrawScreen()
{
    MacUILib_clearScreen();  

    objPos tempPlayer;
    myPlayer->getPlayerPos(tempPlayer);

    objPos tempFood;
    myFood->getFoodPos(tempFood);

    MacUILib_printf("BoardSize: %dx%d,Player Pos: <%d, %d> + %c\n",
                    myGM->getBoardSizeX(), 
                    myGM->getBoardSizeY(),
                    tempPlayer.x, tempPlayer.y, tempPlayer.symbol); 

    int height = myGM->getBoardSizeY();
    int width = myGM->getBoardSizeX();
    
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
        if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
        { // Use to check when reaching end/beginning of board in order to draw sides
            MacUILib_printf("%c", '#');
        }               
        else if (i == tempPlayer.y && j == tempPlayer.x)
        {
            MacUILib_printf("%c", tempPlayer.symbol);
        }

        else if (i == tempFood.y && j == tempFood.x)
        {
            MacUILib_printf("%c", tempFood.symbol);
        }

        else
        {
            MacUILib_printf("%c", ' ');                   //draw blanks in box
        }
    }
    MacUILib_printf("\n"); 
    
    }
    MacUILib_printf("Score: %d",myGM->getScore());
    MacUILib_printf("\nLose flag: %d",myGM->getLoseFlagStatus());
    MacUILib_printf("\nFood Pos: <%d, %d>, + %c\n", tempFood.x, tempFood.y, tempFood.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM; 
    delete myPlayer;
    delete myFood;
}
