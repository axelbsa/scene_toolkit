#include <cstdio>
#include <cstdlib>
#include <vector>

#include <stdint.h>
#include "raylib.h"

#define MIN_INTERVAL (1.0 / 100.0)
#define MAX_LATENCY   0.5

const int screenWidth = 1024;
const int screenHeight = 600;
const Color BACKGROUND = {12, 12, 12};

bool progress = true;
uint64_t left_score = 0;
uint64_t right_score = 0;

const int pad_width = 18;
const int pad_length = 120;
const int BALL_SPEED = 12;

Rectangle right_player_rect = {(screenWidth - pad_width) - 4, 120, pad_width, 120};
Rectangle left_player_rect = {4, 120, pad_width, 120};

enum Dir {UP, DOWN, LEFT, RIGHT};
Dir ball_direction = LEFT;
Vector2 ball_position = {screenWidth / 2, screenHeight / 2};
Vector2 ball_velocity = {500.0, 500.0};


bool check_up_down_collision(Rectangle rect, Dir direction)
{
	switch(direction)
	{
        case LEFT: break;
        case RIGHT: break;
		case UP: 
            if (rect.y <= 0){
                return false;
            }
            break;
		case DOWN: 
            if (rect.y >= screenHeight - pad_length){
                return false;
            }
            break;
	}

    return true;
}

void calculate_ball_velocity()
{
    if (ball_position.x < 0)
    {
        // Left player lost
        progress = false;
    }
    else if (ball_position.x > screenWidth - 7)
    {
        // Right player lost
        progress = false;
    }
    else if (ball_position.y < 0)
    {
        ball_velocity.y *= -1;
    }
    else if (ball_position.y > screenHeight -7)
    {
        ball_velocity.y *= -1;
    }
    
    // check pad hits
    if (CheckCollisionCircleRec(ball_position, 14, right_player_rect))
    {
        // Right pad hit
        ball_velocity.x *= -1.0;
        right_score += 1;
    }
    else if (CheckCollisionCircleRec(ball_position, 14, left_player_rect))
    {
        // Left pad hit
        ball_velocity.x *= -1.0;
        left_score += 1;
    }


}

void Update(float dx)
{
    if (IsKeyDown(KEY_DOWN) && progress)
    {
        if (check_up_down_collision(right_player_rect, DOWN))
            right_player_rect.y += BALL_SPEED;
    }
    else if (IsKeyDown(KEY_UP) && progress)
    {
        if (check_up_down_collision(right_player_rect, UP))
            right_player_rect.y -= BALL_SPEED;
    }

    if (IsKeyDown(KEY_S) && progress)
    {
        if (check_up_down_collision(left_player_rect, DOWN))
            left_player_rect.y += BALL_SPEED;
    }
    else if (IsKeyDown(KEY_W) && progress)
    {
        if (check_up_down_collision(left_player_rect, UP))
            left_player_rect.y -= BALL_SPEED;
    }

    //
    calculate_ball_velocity();

    if (progress == false)
        return;
    ball_position.y = ball_position.y + ball_velocity.y * dx;
    ball_position.x = ball_position.x + ball_velocity.x * dx;

#ifdef DEBUG
    printf("Current time:%f   ",GetFrameTime());
    printf("Dx is now:%f   ",dx);
    printf("flappy_velocity %f\n", flap_velocity_y);
#endif
}


void Draw()
{
    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key

        // Update
        Update(GetFrameTime());

        // Draw
        BeginDrawing();
            ClearBackground(BACKGROUND);
            
            //void DrawRectangleRec(Rectangle rec, Color color);
            DrawRectangleRec(left_player_rect, LIGHTGRAY);
            DrawRectangleRec(right_player_rect, LIGHTGRAY);
            DrawText(FormatText("Score: %i", left_score), 5, 5, 20, VIOLET);
            DrawText(FormatText("Score: %i", right_score), screenWidth - 100, 5, 20, VIOLET);
            //DrawRectangleLines(flappy_vec.x, flappy_vec.y, flappy.width, flappy.height, RED);

            DrawCircleV(ball_position, 12, SKYBLUE);

            if (!progress)
            {
                DrawText("GAME OVER..", screenWidth / 3.0, screenHeight / 2.0, 68, WHITE);
            }


        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
}


int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT); // Use before InitWindow()
    InitWindow(screenWidth, screenHeight, "Friday warm beer pong");
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second


    Draw();

    return 0;
}
