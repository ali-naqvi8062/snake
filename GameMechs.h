#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include "objPos.h"

class GameMechs {
private:
    char input;
    bool exitFlag;
    bool loseFlag;
    int score;
    int boardSizeX;
    int boardSizeY;
    objPos foodPos;
public:
    GameMechs(int boardX = 30, int boardY = 15);
    ~GameMechs();

    bool getExitFlagStatus();
    void setExitTrue();
    bool getLoseFlagStatus();
    void setLoseFlag();
    char getInput();
    void setInput(char thisInput);
    void clearInput();
    int getBoardSizeX();
    int getBoardSizeY();
    int getScore();
    void incrementScore(int addScore);
    void generateFood(objPos blockOff);
    void getFoodPosition(objPos& returnPos);
    bool isPositionFree(int x, int y);
};

#endif