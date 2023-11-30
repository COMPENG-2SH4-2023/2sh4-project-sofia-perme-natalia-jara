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

        void generateFood(objPosArrayList* blockOffList); //blockoff is now entire snake body
        void getFoodPos(objPos &returnPos);
        
};

#endif