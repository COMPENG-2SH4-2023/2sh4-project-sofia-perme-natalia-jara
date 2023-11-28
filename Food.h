#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;


class Food
{
    private:
        objPos foodPos;
        //GameMechs* mainGameMechsRef;

    public:
        Food();
        ~Food();

        objPosArrayList* playerPosList();

        void generateFood(objPos blockOff);// need to upgrade this//currently calling objPos constructor
        void getFoodPos(objPos &returnPos);
        //void regenerateFood(); //new food location is generated when debug key is pressed (iteration 2B)
      
};

#endif