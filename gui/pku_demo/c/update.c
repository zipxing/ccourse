#include "init.h"
#include "update.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

//Update game per frame...
void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;
        if (!pause)
        {
            //Player control
            if (IsKeyPressed(KEY_RIGHT) && (snake[0].speed.x == 0) && allowMove)
            {
                snake[0].speed = (Vector2){ SQUARE_SIZE, 0 };
                allowMove = false;
            }
            if (IsKeyPressed(KEY_LEFT) && (snake[0].speed.x == 0) && allowMove)
            {
                snake[0].speed = (Vector2){ -SQUARE_SIZE, 0 };
                allowMove = false;
            }
            if (IsKeyPressed(KEY_UP) && (snake[0].speed.y == 0) && allowMove)
            {
                snake[0].speed = (Vector2){ 0, -SQUARE_SIZE };
                allowMove = false;
            }
            if (IsKeyPressed(KEY_DOWN) && (snake[0].speed.y == 0) && allowMove)
            {
                snake[0].speed = (Vector2){ 0, SQUARE_SIZE };
                allowMove = false;
            }

            //Snake movement
            for (int i = 0; i < counterTail; i++) 
                snakePosition[i] = snake[i].position;

            if ((framesCounter%90) == 0)
            {
                if(!phyInited) 
                {
                    // Create floor rectangle physics body
                    PhysicsBody floor = CreatePhysicsBodyRectangle(
                            (Vector2){ screenWidth*0.75, screenHeight }, 360, 100, 10);
                    // Disable body state to convert it to static
                    floor->enabled = false;
                    PhysicsBody circle = CreatePhysicsBodyCircle(
                            (Vector2){ screenWidth*0.75, screenHeight/2 }, 45, 10);
                    circle->enabled = false;
                    phyInited = true;
                }
                if(framesCounter%2==0)
                    CreatePhysicsBodyPolygon(
                            GetMousePosition(),
                            GetRandomValue(20, 80),
                            GetRandomValue(3, 8),
                            10);
                else
                    CreatePhysicsBodyCircle(
                            GetMousePosition(),
                            GetRandomValue(10, 45),
                            10);
                // Destroy falling physics bodies
                int bodiesCount = GetPhysicsBodiesCount();
                for (int i = bodiesCount - 1; i >= 0; i--)
                {
                    PhysicsBody body = GetPhysicsBody(i);
                    if (body != NULL && (body->position.y > screenHeight*2)) 
                        DestroyPhysicsBody(body);
                }
            }

            if ((framesCounter%30) == 0)
            {
                for (int i = 0; i < counterTail; i++)
                {
                    if (i == 0)
                    {
                        snake[0].position.x += snake[0].speed.x;
                        snake[0].position.y += snake[0].speed.y;
                        allowMove = true;
                    }
                    else snake[i].position = snakePosition[i-1];
                }
            }

            //Wall behaviour
            if (((snake[0].position.x) > (screenWidth/2 - offset.x)) ||
                ((snake[0].position.y) > (screenHeight - offset.y)) ||
                (snake[0].position.x < 0) || (snake[0].position.y < 0))
            {
                gameOver = true;
            }

            //Collision with yourself
            for (int i = 1; i < counterTail; i++)
            {
                if ((snake[0].position.x == snake[i].position.x) &&
                        (snake[0].position.y == snake[i].position.y))
                    gameOver = true;
            }

            //Fruit position calculation
            if (!fruit.active)
            {
                fruit.active = true;
                fruit.position = (Vector2) {
                    GetRandomValue(0, (screenWidth/2/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2,
                    GetRandomValue(0, (screenHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2
                };

                for (int i = 0; i < counterTail; i++)
                {
                    while ((fruit.position.x == snake[i].position.x) &&
                            (fruit.position.y == snake[i].position.y))
                    {
                        fruit.position = (Vector2){
                            GetRandomValue(0, (screenWidth/2/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2,
                            GetRandomValue(0, (screenHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2
                        };
                        i = 0;
                    }
                }
            }

            //Collision
            if ((snake[0].position.x < (fruit.position.x + fruit.size.x) &&
                 (snake[0].position.x + snake[0].size.x) > fruit.position.x) &&
                 (snake[0].position.y < (fruit.position.y + fruit.size.y) &&
                 (snake[0].position.y + snake[0].size.y) > fruit.position.y))
            {
                snake[counterTail].position = snakePosition[counterTail - 1];
                counterTail += 1;
                fruit.active = false;
            }

            framesCounter++;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            ClosePhysics();
            InitGame();
            gameOver = false;
            phyInited = false;
        }
    }
    camera.fovy = 45.0f - (framesCounter * 0.05f);
}
