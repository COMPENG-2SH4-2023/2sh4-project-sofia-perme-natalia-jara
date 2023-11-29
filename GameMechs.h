#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design. 

    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;
        
        int boardSizeX;
        int boardSizeY;

        int foodNum;   //number of food items to be generated
        int featuresNum; //num of special features


    public:
        GameMechs();
        GameMechs(int boardX, int boardY,int numFood,int numFeatures);
        ~GameMechs();
        
        bool getExitFlagStatus();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        int getFeaturesNum();
        int getFoodNum();

        int getScore();
        void incrementScore();

        bool getLoseFlagStatus();
        bool setLoseFlag();
      
};

#endif