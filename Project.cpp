#include <iostream>
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "MacUILib.h"

using namespace std;

#define DELAY_CONST 25000

GameMechs game;
Food foodManager (&game);
Player snake(&game, &foodManager);
char input;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    //loop while "space" key not entered or no body collision
    while(game.getExitFlagStatus() == false && game.getLoseFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    foodManager.generateFood(*(snake.getPlayerPos()));
}

void GetInput(void) {
    if (MacUILib_hasChar()) {
        input = MacUILib_getChar();
        game.setInput(input);
        snake.updatePlayerDir();
    }
}

void RunLogic(void)
{
    // Update the snake's direction and move it based on input
    snake.updatePlayerDir();
    snake.movePlayer();

    // Check for food consumption
    int shouldGrowBy = snake.checkFoodConsumption();
    if (shouldGrowBy != 0) {
        objPos headPos;
        snake.getPlayerPos()->getHeadElement(headPos);
        snake.increasePlayerLength(shouldGrowBy);
        if (shouldGrowBy == 10)
        {
            game.incrementScore(5);
            foodManager.generateFood(*(snake.getPlayerPos()));
        }
        else
        {
            game.incrementScore(1);
            foodManager.generateFood(*(snake.getPlayerPos()));
        }
        
        if (foodManager.getFoodList()->getSize() == 0)
        {
            foodManager.generateFood(*(snake.getPlayerPos()));
        }
    }

    // Check for collision with the snake's body
    if (snake.checkSelfCollision())
    {
        game.setLoseFlag();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Draw the game board with the snake and food
    for (int y = 0; y < game.getBoardSizeY(); ++y) {
        for (int x = 0; x < game.getBoardSizeX(); ++x) {
            if (y == 0 || y == game.getBoardSizeY() - 1 || x == 0 || x == game.getBoardSizeX() - 1) {
                MacUILib_printf("#");
            }
            else {
                // draw the food positions on the board
                bool isFoodDrawn = false;
                for (int i = 0; i < foodManager.getFoodList()->getSize(); ++i) {
                    objPos foodPos;
                    foodManager.getFoodList()->getElement(foodPos, i);
                    if (x == foodPos.x && y == foodPos.y) {
                        MacUILib_printf("%c", foodPos.getSymbol());
                        isFoodDrawn = true;
                        break; // Once food is drawn, no need to check other food positions
                    }
                }

                // If no food was drawn at this position, check if it's a snake segment
                if (!isFoodDrawn) {
                    bool isBodySegment = false;
                    for (int i = 0; i < snake.getPlayerPos()->getSize(); ++i) {
                        objPos segment;
                        snake.getPlayerPos()->getElement(segment, i);
                        if (x == segment.x && y == segment.y) {
                            MacUILib_printf("%c", segment.getSymbol());
                            isBodySegment = true;
                            break; // Once the segment is drawn, no need to check other segments
                        }
                    }
                    // If neither food nor snake segment is at this position, draw a space
                    if (!isBodySegment) {
                        MacUILib_printf(" ");
                    }
                }
            }
        }
        MacUILib_printf("\n"); // New line at the end of each row
    }
    MacUILib_printf("\nScore: %d\n", game.getScore()); // Print the score below the game board
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    if (game.getExitFlagStatus())
    {
        MacUILib_printf("Thank you for playing. Your score: %d\n",game.getScore());
    }

    if (game.getLoseFlagStatus())
    {
        MacUILib_printf("You lose. Your score: %d\n", game.getScore());
    }
    MacUILib_uninit();
}
