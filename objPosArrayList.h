#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();
        ~objPosArrayList();

        int getSize();
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        void getHeadElement(objPos &returnPos);
        void getTailElement(objPos &returnPos);
        void getElement(objPos &returnPos, int index);
        void getByPos(objPos &returnPos,int x,int y);
        bool containsPos(objPos refPos);
        void clear();
};

#endif