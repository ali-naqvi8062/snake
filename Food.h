#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "GameMechs.h"

class Food {
private:
    objPosArrayList* foodBucket; // List of all food objects
    GameMechs* gameMechanicsRef; // Reference to the game mechanics
public:
    Food(GameMechs* thisGMRef);
    ~Food();

    void generateFood(objPosArrayList& playerBody);
    void getFoodPos(objPos& returnPos);
    objPosArrayList* getFoodList();
};

#endif // FOODMANAGER_H