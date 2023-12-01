#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete [] aList;
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    for (int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]);
    }
    aList[0].setObjPos(thisPos);
    
    listSize++;

}

void objPosArrayList::insertTail(objPos thisPos)
{
   
    aList[listSize].setObjPos(thisPos);
    
    listSize++;

}

void objPosArrayList::removeHead()
{
    for (int i=0;i<listSize-1;i++)
    {
        aList[i].setObjPos(aList[i+1]);
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    listSize--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize-1]);
}


void objPosArrayList::getElement(objPos &returnPos, int index)
{
    return returnPos.setObjPos(aList[index]);
}