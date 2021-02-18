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

#define WAVE_NUM 40
#define OBJ_COUNT 100
#define FIGHTER_SPEED 10
#define ZIDAN_SPEED 8
#define FIRE_RATE 5

static int framesCounter = 0;
static Vector2 fighterPos;
static Vector2 zidanPos[OBJ_COUNT];

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

// 对象池，element中存储对象ID
// 并且按ID对应的下标位置存储，例如添加ID=2，就是赋值element[2] = 2
// ID对应位置是-1，表示池中没有这个ID
// count表示当前池中拥有的ID数
typedef struct obj_pool
{
    int element[OBJ_COUNT];
    int count;
} OBJPOOL;

//初始化count个连续ID，注意count不能大于OBJ_COUNT
void op_init(OBJPOOL *op, int count)
{
    for (int i = 0; i < OBJ_COUNT; i++)
        op->element[i] = -1;
    for (int i = 0; i < count; i++)
        op->element[i] = i;
    op->count = count;
}

//按ID从池中取出并删除
int op_getid(OBJPOOL *op, int id)
{
    if (op->count == 0)
        return -1;
    op->count--;
    op->element[id] = -1;
    return op->element[op->count];
}

//添加某个ID
int op_putid(OBJPOOL *op, int id)
{
    if (op->count >= OBJ_COUNT)

        return -1;
    op->count++;
    op->element[id] = id;
    return op->count;
}

//从池中取出一个ID并返回,如果池为空返回-1
int op_get(OBJPOOL *op)
{
    for (int i = 0; i < OBJ_COUNT; i++)
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

//两个全局对象池，一个放空闲的子弹，一个放活跃的子弹
OBJPOOL free_pool, act_pool;

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

//发出子弹，从free_pool中移到act_pool中
void fire()
{
    int freeid = op_get(&free_pool);
    if (freeid == -1)
    {
        printf("getfreeid====================================-1\n");
        return;
    }
    op_putid(&act_pool, freeid);
    zidanPos[freeid].x = fighterPos.x;
    zidanPos[freeid].y = fighterPos.y;
}

//子弹回收
void recycle(int id)
{
    op_getid(&act_pool, id);
    op_putid(&free_pool, id);

    /*
    //DEBUG
    printf("act(%d):",act_pool.count);
    for (int i = 0; i < OBJ_COUNT; i++)
    {
        if (act_pool.element[i] != -1)

            printf("%d ", act_pool.element[i]);
    }
    printf("\n");
    printf("free(%d):",free_pool.count);
    for (int j = 0; j < OBJ_COUNT; j++)
    {
        if (free_pool.element[j] != -1)
            printf("%d ", free_pool.element[j]);
    }
    */
}

void zdfly()
{
    for (int i = 0; i < OBJ_COUNT; i++)
    {
        int actid = act_pool.element[i];
        if (actid != -1)
        {
            zidanPos[actid].y-=ZIDAN_SPEED;
            if (zidanPos[actid].y <= 0)
            {
                recycle(actid);
            }
        }
    }
}

void InitGame(void)
{
    framesCounter = 0;
    srand(0);
    op_init(&free_pool, OBJ_COUNT);
    op_init(&act_pool, 0);
    fighterPos.x = 200;
    fighterPos.y = 200;
}

// Update game (one frame)

void UpdateGame(void)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        fighterPos.x += ZIDAN_SPEED;
        if (fighterPos.x > screenWidth)
            fighterPos.x = screenWidth;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        fighterPos.x -= ZIDAN_SPEED;
        if (fighterPos.x < 0)
            fighterPos.x = 0;
    }

    if (IsKeyDown(KEY_UP))
    {
        fighterPos.y -= ZIDAN_SPEED;
        if (fighterPos.y < 0)
            fighterPos.y = 0;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        fighterPos.y += ZIDAN_SPEED;
        if (fighterPos.y > screenHeight)
            fighterPos.y = screenHeight;
    }

    if ((framesCounter % FIRE_RATE) == 0)
    {
        fire();
    }
    zdfly();

    framesCounter++;
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);

    //绘制波浪...
    Color col[16] = {
        LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE,
        PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE,
        BLUE, DARKBLUE, PURPLE};
    for (int i = 0; i < WAVE_NUM; i++)
        DrawCircle(20 * i, 20 * sin((framesCounter / 5) - 20 * i) + 100, 3,
                   col[rand()%16] );

    //绘制本人战斗机
    DrawCircle(fighterPos.x, fighterPos.y, 20, WHITE);

    //绘制子弹
    for (int i = 0; i < OBJ_COUNT; i++)
    {
        int actid = act_pool.element[i];
        if (actid != -1)
        {
            DrawCircle(zidanPos[actid].x, zidanPos[actid].y, 5, RED);
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
