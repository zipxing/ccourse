#ifndef __SNAKE__
#define __SNAKE__

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define SNAKE_LENGTH   256
#define SQUARE_SIZE     31

typedef struct Snake {
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
} Snake;

typedef struct Food {
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} Food;

class Game {
public:
    static const int screenWidth = 640;
    static const int screenHeight = 480;

    static int framesCounter;
    static bool gameOver;
    static bool pause;

    static Food fruit;
    static Snake snake[SNAKE_LENGTH];
    static Vector2 snakePosition[SNAKE_LENGTH];
    static bool allowMove;
    static Vector2 offset;
    static int counterTail;

    static Camera camera;



}

#endif
