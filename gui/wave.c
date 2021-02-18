#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 1000;
static const int screenHeight = 600;

static int framesCounter = 0;
#define NUM 40
#define OBJCOUNT 100
#define ZIDANSPEED 8
#define FIRERATE 5
static char point[NUM];
static int x = 0, y = 0;
static Vector2 pointPos;
static Vector2 zidanPos[OBJCOUNT];

Camera camera = {0};
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
//-----------------------------------------------------------------------------------

typedef struct obj_pool
{
    int element[OBJCOUNT];
    int count;
} OBJPOOL;

OBJPOOL free_pool, act_pool;

void op_init(OBJPOOL *op, int count)
{
    for (int i = 0; i < OBJCOUNT; i++)
        op->element[i] = -1;
    for (int i = 0; i < count; i++)
        op->element[i] = i;
    op->count = count;
}

int op_getid(OBJPOOL *op, int id)
{
    if (op->count == 0)
        return -1;
    op->count--;
    op->element[id] = -1;
    return op->element[op->count];
}

int op_putid(OBJPOOL *op, int id)
{
    if (op->count >= OBJCOUNT)

        return -1;
    op->count++;
    op->element[id] = id;
    return op->count;
}

int op_get(OBJPOOL *op)
{
    for (int i = 0; i < OBJCOUNT; i++)
    {
        if (op->element[i] != -1)
        {
            op->element[i] = -1;
            op->count--;
            return i;
        }
    }
    return -1;
}
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

// Initialize game variable
void fire()
{
    int freeid = op_get(&free_pool);
    if (freeid == -1)
    {
        printf("getfreeid====================================-1\n");
        return;
    }
    op_putid(&act_pool, freeid);
    zidanPos[freeid].x = pointPos.x;
    zidanPos[freeid].y = pointPos.y;
}

void recycle111(int id)
{
    op_getid(&act_pool, id);

    op_putid(&free_pool, id);
    printf("act(%d):",act_pool.count);
    for (int i = 0; i < OBJCOUNT; i++)
    {
        if (act_pool.element[i] != -1)

            printf("%d ", act_pool.element[i]);
    }
    printf("\n");
    printf("free(%d):",free_pool.count);
    for (int j = 0; j < OBJCOUNT; j++)
    {
        if (free_pool.element[j] != -1)
            printf("%d ", free_pool.element[j]);
    }
}
void zdfly()
{
    for (int i = 0; i < OBJCOUNT; i++)
    {
        int actid = act_pool.element[i];
        if (actid != -1)
        {
            zidanPos[actid].y-=ZIDANSPEED;
            if (zidanPos[actid].y <= 0)
            {
                recycle111(actid);
                printf("recycle111111111\n");
            }
        }
    }
}

void InitGame(void)
{
    framesCounter = 0;
    srand(0);
    op_init(&free_pool, OBJCOUNT);
    op_init(&act_pool, 0);
    /*camera.position = (Vector3){0.0f, 10.0f, 10.0f};
    camera.target = (Vector3){1.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.type = CAMERA_PERSPECTIVE;*/
}

// Update game (one frame)

void UpdateGame(void)
{
    if ((framesCounter % 10) == 0)
    {
        for (int i = 0; i < NUM; i++)
        {
            y = 80 * sin(framesCounter - 20 * i) + 100;
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        pointPos.x += 10;
        if (pointPos.x > 1000)
            pointPos.x = 1000;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        pointPos.x -= 10;
        if (pointPos.x < 0)
            pointPos.x = 0;
    }

    if (IsKeyDown(KEY_UP))
    {
        pointPos.y -= 10;
        if (pointPos.y < 0)
            pointPos.y = 0;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        pointPos.y += 10;
        if (pointPos.y > 600)
            pointPos.y = 600;
    }
    if ((framesCounter % FIRERATE) == 0)
    {
        fire();
    }
    zdfly();

    camera.fovy = 45.0f - (framesCounter * 0.05f);

    framesCounter++;
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);
    Color col[16] = {
        LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE,
        PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE,
        BLUE, DARKBLUE, PURPLE};
    for (int i = 0; i < NUM; i++)
    {
        DrawCircle(20 * i, 20 * sin((framesCounter / 5) - 20 * i) + 100, 5,
                   RED );
    }
    DrawCircle(pointPos.x, pointPos.y, 20, WHITE);
    for (int i = 0; i < OBJCOUNT; i++)
    {
        int actid = act_pool.element[i];
        if (actid != -1)
        {
            DrawCircle(zidanPos[actid].x, zidanPos[actid].y, 5, RED);
            //printf("?&&&&&&&&\n");
        }
    }

    /*BeginMode3D(camera);

    DrawCube((Vector3){-4.0f, 0.0f, 2.0f}, 2.0f, 5.0f, 2.0f, RED);
    DrawCubeWires((Vector3){-4.0f, 0.0f, 2.0f}, 2.0f, 5.0f, 2.0f, GOLD);
    DrawCubeWires((Vector3){-4.0f, 0.0f, -2.0f}, 3.0f, 6.0f, 2.0f, MAROON);

    DrawSphere((Vector3){-1.0f, 0.0f, -2.0f}, 1.0f, GREEN);
    DrawSphereWires((Vector3){1.0f, 0.0f, 2.0f}, 2.0f, 16, 16, LIME);

    DrawCylinder((Vector3){4.0f, 0.0f, -2.0f}, 1.0f, 2.0f, 3.0f, 4, SKYBLUE);
    DrawCylinderWires((Vector3){4.0f, 0.0f, -2.0f}, 1.0f, 2.0f, 3.0f, 4, DARKBLUE);
    DrawCylinderWires((Vector3){4.5f, -1.0f, 2.0f}, 1.0f, 1.0f, 2.0f, 6, BROWN);

    DrawCylinder((Vector3){1.0f, 0.0f, -4.0f}, 0.0f, 1.5f, 3.0f, 8, GOLD);
    DrawCylinderWires((Vector3){1.0f, 0.0f, -4.0f}, 0.0f, 1.5f, 3.0f, 8, PINK);

    DrawGrid(10, 1.0f); // Draw a grid

    EndMode3D();*/

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
