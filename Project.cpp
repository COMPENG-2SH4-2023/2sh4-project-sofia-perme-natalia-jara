#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM; //should i be using destructor function to remove from heap or just delete call?
Player* myPlayer;


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
    //exit flag removed because object myGM already has flag = false
}

void GetInput(void)
{
    //myGM->getInput(); //or should be setInput()?
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen()
{
    MacUILib_clearScreen();  

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);

    MacUILib_printf("BoardSize: %dx%d,Player Pos: <%d, %d> + %c\n",
                    myGM->getBoardSizeX(), 
                    myGM->getBoardSizeY(),
                    tempPos.x, tempPos.y, tempPos.symbol); 

    int height=myGM->getBoardSizeY();
    int width=myGM->getBoardSizeX();
    
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
        if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                { // Use to check when reaching end/beginning of board in order to draw sides
                    MacUILib_printf("#");
                }               
        else if (i==tempPos.y&& j==tempPos.x){
            printf("%c", tempPos.symbol);
        }
        else
                {
                    MacUILib_printf(" ");                   //draw blanks in box
                }
    }
    MacUILib_printf("\n"); 
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
  
    MacUILib_uninit();

    //delete myGM; //not sure if correct
}
