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
        objPosArrayList* foodBucket;

        bool contains(objPosArrayList* blockOffList,int x,int y);
        
        // int numFood;   //number of food items to be generated
        // int numFeatures; //num of special features

    public:
        Food(GameMechs* thisGMRef,objPosArrayList* foodBucket);
        ~Food();

        void generateFood(objPosArrayList* blockOffList, bool special);// need to upgrade this
        void getFoodPos(objPos &returnPos);
        //void regenerateFood(); //new food location is generated when debug key is pressed (iteration 2B)
      
};

#endif