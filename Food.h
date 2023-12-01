#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"


class Food
{
    private:
        GameMechs* mainGameMechsRef;
        objPosArrayList* foodBucket;

        // internal function to check generated coordinates against blockOffList
        bool contains(objPosArrayList* blockOffList,int x,int y);
        
        // generates food where positions must not overlap blockOffList elements
        bool generateFood(objPosArrayList* blockOffList, bool special);
        
    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        // generates food bucket where positions must not overlap blockOffList elements
        int generateFoodBucket(objPosArrayList* blockOffList);

        // / returns generated food bucket
        objPosArrayList* getFoodBucket();
        //generates the different foodBucket symbols
        char generateSymbol(bool special); 
};

#endif