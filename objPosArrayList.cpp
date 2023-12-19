#include "objPosArrayList.h"

objPosArrayList::objPosArrayList() : sizeList(0), sizeArray(ARRAY_MAX_CAP) {
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList() {
    delete[] aList;
}

int objPosArrayList::getSize() {
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos) {
    if (sizeList < ARRAY_MAX_CAP) {
        for (int i = sizeList; i > 0; --i) { //loop through everything from the tail of the snake to the head
            aList[i] = aList[i - 1]; //everything gets shifted to make space for the new head
        }
        aList[0] = thisPos; //inserts the new head
        ++sizeList;
    }
}

void objPosArrayList::removeHead() {
    if (sizeList > 0) {
        for (int i = 0; i < sizeList - 1; ++i) {
            aList[i] = aList[i + 1];
        }
        --sizeList;
    }
}

void objPosArrayList::insertTail(objPos thisPos) {
    if (sizeList < ARRAY_MAX_CAP) {
        aList[sizeList] = thisPos;
        ++sizeList;
    }
}

void objPosArrayList::removeTail() {
    if (sizeList > 0) {
        --sizeList;
    }
}

void objPosArrayList::clear() {
    while (getSize() > 0) {
        removeTail();
    }
}

void objPosArrayList::getHeadElement(objPos& returnPos) {
    if (sizeList > 0) {
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos& returnPos) {
    if (sizeList > 0) {
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos& returnPos, int index) {
    if (index >= 0 && index < sizeList) {
        returnPos = aList[index];
    }
}

void objPosArrayList::removeElement(int index) {
    if (index >= 0 && index < sizeList) {
        for (int i = index; i < sizeList - 1; ++i) {
            aList[i] = aList[i + 1]; // Shift elements down to fill the gap
        }
        sizeList--; // Decrease the size of the list
    }
}