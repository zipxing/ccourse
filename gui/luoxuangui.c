/*******************************************************************************************
*
*   raylib - sample game: snake
*
*   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <string.h>
#include <stdio.h>
typedef enum dir
{
    RIGHT = 0,
    DOWN,
    LEFT,
    UP
} DIR;

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 1200;
static const int screenHeight = 800;

static int framesCounter = 0;
static int numberCounter = 0;
#define NUM 10
static int buf[NUM][NUM];
static DIR d = RIGHT;
static int x = 0, y = 0;
//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);        // Initialize game
static void UpdateGame(void);      // Update game (one frame)
static void DrawGame(void);        // Draw game (one frame)
static void UnloadGame(void);      // Unload game
static void UpdateDrawFrame(void); // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "sample game: snake");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame(); // Unload loaded data (textures, sounds, models...)

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables

void move(DIR d, int *x, int *y)
{
    switch (d)
    {
    case RIGHT:
        (*x)++;
        break;
    case DOWN:
        (*y)++;
        break;
    case LEFT:
        (*x)--;
        break;
    case UP:
        (*y)--;
        break;
    default:;
    }
}
void InitGame(void)
{
    framesCounter = 0;

    memset(buf, 0, sizeof(int) * NUM * NUM);
}

// Update game (one frame)

void UpdateGame(void)
{
    if ((framesCounter % 10) == 0 && numberCounter<NUM*NUM)
    {
        buf[y][x] = numberCounter + 1;
        int x1, y1;
        x1 = x;
        y1 = y;
        move(d, &x, &y);

        int isvalid = 1;
        if (x >= NUM || x < 0 || y >= NUM || y < 0) //越界
        {
            isvalid = 0;
        }
        else if (buf[y][x] != 0)
        {
            isvalid = 0;
        }
        if (!isvalid)
        {
            x = x1;
            y = y1;
            d = (d + 1) % 4;
            move(d, &x, &y);
        }
        numberCounter++;
    }
    framesCounter++;
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    char strnum[4];
    
    for (int i = 0; i < NUM; i++)
    {
        for(int j=0;j<NUM;j++)
        {   
            if(buf[i][j]!=0){
                sprintf(strnum,"%d",buf[i][j]);
            DrawText(strnum, 80 * j, 80 * i, 40, BLACK);
            }
        }
        
    }

    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}
