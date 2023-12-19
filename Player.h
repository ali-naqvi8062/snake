#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* foodRef);
        ~Player();

        objPosArrayList* getPlayerPos();
        void updatePlayerDir();
        void movePlayer();
        void increasePlayerLength(int growBy);
        bool checkSelfCollision();
        int checkFoodConsumption();
    private:
        objPosArrayList* playPosList;
        enum Dir myDir;
        int shouldGrowBy;
        GameMechs* mainGameMechsRef;
        Food* foodRef;
};

#endif