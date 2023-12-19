#include "Food.h"
#include <cstdlib>

Food::Food(GameMechs* thisGMRef)
{
    gameMechanicsRef = thisGMRef; //will be helpful when we need to access methods inside of GameMechs class
    foodBucket = new objPosArrayList();
}

Food::~Food() 
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList& playerBody) 
{
    foodBucket->clear();

    // Generate new food items
    for (int i = 0; i < 5; ++i) 
    { // Generate 5 food items
        int foodX, foodY;
        bool positionIsFree;
        do 
        {
            positionIsFree = true; // Assume the position is free until checked
            foodX = rand() % (gameMechanicsRef->getBoardSizeX() - 2) + 1;
            foodY = rand() % (gameMechanicsRef->getBoardSizeY() - 2) + 1;

            // Check if the generated position overlaps with the snake's body
            for (int j = 0; j < playerBody.getSize(); ++j) 
            {
                objPos segment; //temporary objPos we need to utilize getElement() in the line below
                playerBody.getElement(segment, j);
                if (segment.x == foodX && segment.y == foodY) 
                {
                    positionIsFree = false; // Position is not free as it overlaps with the snake
                    break; // No need to check further; break out of the inner loop
                }
            }
        } while (!positionIsFree); // Keep generating positions until a free one is found

        // Create normal food
        objPos newFood(foodX, foodY, 'F');

        // Randomly decide if this food is special
        if (rand() % 100 < 15) // 15% chance to be special food
        { 
            newFood.symbol = 'S'; // 'S' for special food
        }

        // Add the new food to the foodBucket
        foodBucket->insertTail(newFood);
    }
}

void Food::getFoodPos(objPos& returnPos) {
    if (foodBucket -> getSize() > 0) {
        foodBucket -> getHeadElement(returnPos);
    }
    else {
        // If there are no food items, set an invalid position
        returnPos.setObjPos(-1, -1, ' ');
    }
}

objPosArrayList* Food::getFoodList()
{
    return foodBucket;
}