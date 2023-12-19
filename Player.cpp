#include "Player.h"
#include <iostream>

Player::Player(GameMechs* thisGMRef, Food* foodRef) 
{
    mainGameMechsRef = thisGMRef;
    this->foodRef = foodRef;
    myDir = STOP;
    playPosList = new objPosArrayList();
    objPos playerPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playPosList->insertHead(playerPos);
    shouldGrowBy = 0;
}


Player::~Player() 
{
    delete playPosList; //no longer needed when game is over
}

objPosArrayList* Player::getPlayerPos() 
{
    return playPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    if (input != 0)
    {
        switch (toupper(input))
        {
            case ' ':
                mainGameMechsRef ->setExitTrue();
                break;

            case 'W':
                if (this->myDir == LEFT || this->myDir == RIGHT || this->myDir == STOP) {
                    this->myDir = UP;
                }
                break;

            case 'S':
                if (this->myDir == LEFT || this->myDir == RIGHT || this->myDir == STOP) {
                    this->myDir = DOWN;
                }
                break;

            case 'A':
                if (this->myDir == UP || this->myDir == DOWN || this->myDir == STOP) {
                    this->myDir = LEFT;
                }
                break;

            case 'D':
                if (this->myDir == UP || this->myDir == DOWN || this->myDir == STOP) {
                    this->myDir = RIGHT;
                }
                break;
            default:
                break;
        }
        input = 0;
    }
}

void Player::movePlayer() 
{
    // Get the current head position
    objPos currentHead;
    playPosList->getHeadElement(currentHead);

    // Calculate the new head position based on the current direction
    int newX = currentHead.x;
    int newY = currentHead.y;

    switch (myDir) {
    case UP:
        if (newY > 1) {
            newY--;
        }
        else {
            newY = mainGameMechsRef->getBoardSizeY() - 2;
        }
        break;
    case DOWN:
        if (newY < mainGameMechsRef->getBoardSizeY() - 2) {
            newY++;
        }
        else {
            newY = 1;
        }
        break;
    case LEFT:
        if (newX > 1) {
            newX--;
        }
        else {
            newX = mainGameMechsRef->getBoardSizeX() - 2;
        }
        break;
    case RIGHT:
        if (newX < mainGameMechsRef->getBoardSizeX() - 2) {
            newX++;
        }
        else {
            newX = 1;
        }
        break;
    case STOP:
        return;
    default:
        return;
    }

    //add the head and set it's new position
    currentHead.setObjPos(newX, newY, currentHead.getSymbol());

    playPosList->insertHead(currentHead);

    //if player did not grow, remove the tail making it seem like the player moved
    if (shouldGrowBy <= 0) {
        playPosList->removeTail();
    }
    else { //don't remove the tail, and reset helper flag
        shouldGrowBy--;
    }
}

bool Player::checkSelfCollision() 
{
    for (int i = 1; i < playPosList->getSize(); ++i) //loop through entire body array
    {
        objPos bodySegment;
        playPosList->getElement(bodySegment, i);

        objPos headPos;
        playPosList->getHeadElement(headPos);

        if (headPos.x == bodySegment.x && headPos.y == bodySegment.y) //player position is on one of the body segment
        {
            return true;
        }
    }
    return false;
}

void Player::increasePlayerLength(int growBy) 
{
    shouldGrowBy = growBy;
}

int Player::checkFoodConsumption() 
{
    objPos playerPos;
    this->getPlayerPos()->getHeadElement(playerPos);

    for (int i = 0; i < foodRef->getFoodList()->getSize(); ++i) 
    {
        objPos foodPos;
        foodRef->getFoodList()->getElement(foodPos, i);
        if (playerPos.x == foodPos.x && playerPos.y == foodPos.y) 
        { // Player position is food pos
            int growthAmt;
            if (foodPos.getSymbol() == 'S')
                growthAmt = 10;
            else
                growthAmt = 1;
            foodRef->getFoodList()->removeElement(i); // Remove the consumed food item
            return growthAmt;
        }
    }
    return 0; // No food consumed
}