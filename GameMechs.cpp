#include "GameMechs.h"
#include <cstdlib>
#include <ctime>
#include "objPos.h"

GameMechs::GameMechs(int boardX, int boardY) :
    input(0), exitFlag(false), loseFlag(false), score(0), boardSizeX(boardX), boardSizeY(boardY) 
{
    srand((unsigned int)time(NULL));
}

GameMechs::~GameMechs()  // no internal members on heap
{
}

bool GameMechs::getExitFlagStatus() 
{ 
    return exitFlag; 
}

void GameMechs::setExitTrue() 
{ 
    exitFlag = true; 
}

bool GameMechs::getLoseFlagStatus() 
{ 
    return loseFlag; 
}

void GameMechs::setLoseFlag() 
{ 
    loseFlag = true; 
}

char GameMechs::getInput() 
{ 
    return input; 
}

void GameMechs::setInput(char thisInput) 
{ 
    input = thisInput; 
}

void GameMechs::clearInput() 
{
    input = 0; 
}

int GameMechs::getBoardSizeX() 
{ 
    return boardSizeX; 
}

int GameMechs::getBoardSizeY() 
{ 
    return boardSizeY; 
}

int GameMechs::getScore() 
{ 
    return score; 
}

void GameMechs::incrementScore(int addScore) 
{ 
    score += addScore; 
}