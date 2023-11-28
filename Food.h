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
        GameMechs* mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOffList);// need to upgrade this
        void getFoodPos(objPos &returnPos);
        //void regenerateFood(); //new food location is generated when debug key is pressed (iteration 2B)
      
};

#endif