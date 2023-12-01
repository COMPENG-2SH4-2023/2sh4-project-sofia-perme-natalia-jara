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
        GameMechs* mainGameMechsRef;
        objPosArrayList* foodBucket;

        // internal function to check generated coordinates against blockOffList
        bool contains(objPosArrayList* blockOffList,int x,int y);
        

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        // generates food where positions must not overlap blockOffList elements
        void generateFood(objPosArrayList* blockOffList);

        // generates food bucket where positions must not overlap blockOffList elements
        void generateFoodBucket(objPosArrayList* blockOffList);

        // / returns generated food bucket
        objPosArrayList* getFoodBucket();
        
};

#endif