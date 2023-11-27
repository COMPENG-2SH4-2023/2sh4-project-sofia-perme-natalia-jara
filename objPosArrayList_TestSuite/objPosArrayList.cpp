#include "objPosArrayList.h"
#include <stdexcept>
#include <iostream>
using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList=new objPos[ARRAY_MAX_CAP];
    listSize=0;
    arrayCapacity=ARRAY_MAX_CAP;
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
    if (listSize<ARRAY_MAX_CAP)
    {
        for (int i=listSize;i>0;i--)
        {
            aList[i].setObjPos(aList[i-1]);
        }
        aList[0].setObjPos(thisPos);
        
        listSize++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
   if (listSize<ARRAY_MAX_CAP)
   {
        aList[listSize].setObjPos(thisPos);
        listSize++;
   }

}

void objPosArrayList::removeHead()
{
    if (listSize>0)
    {
        for (int i=0;i<listSize-1;i++)
        {
            aList[i].setObjPos(aList[i+1]);
        }

        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    if (listSize>0)
    {
        listSize--;
    }
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
    if (index < 0)
    {
        throw std::out_of_range("Invalid indexes.");
        // cerr << "\nlistSize: " << listSize << "  invalid index: " << index;
    }
    return returnPos.setObjPos(aList[index]);
}