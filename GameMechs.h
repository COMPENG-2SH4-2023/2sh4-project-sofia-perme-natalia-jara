#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"


class GameMechs
{
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
        void incrementScore(char symbol);
        void decreaseScore();

        bool getLoseFlagStatus();
        bool setLoseFlag();
      
};

#endif