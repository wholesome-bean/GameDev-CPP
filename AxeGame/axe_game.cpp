#include "raylib.h"
#include <ctime>    // For seeding the random number generator
#include <cstdlib>  // For rand() and srand()

int main()
{
    // Window Size
    int Width = 800;
    int Height = 450;

    // Circle Details
    float circle_radius = 25;
    float circle_x = (Width / 2) - 50;
    float circle_y = (Height / 2) - 50;

    // Axe Details
    float axe_length = 50;
    float axe_x = 400;
    float axe_y = 0;
    float direction_x = 10;
    float direction_y = 10;

    // Power-up Details
    float powerup_radius = 15;
    float powerup_x = (rand() % (Width - (int)(2 * powerup_radius))) + powerup_radius;
    float powerup_y = (rand() % (Height - (int)(2 * powerup_radius))) + powerup_radius;
    bool powerup_active = false;
    float powerup_timer = 0;

    // Game Variables
    int score = 0;
    int lives = 3;
    bool game_over = false;

    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    InitWindow(Width, Height, "Richard's Enhanced Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE); // prevents flickering

        // Game logic begins

        // Check for collision
        if (CheckCollisionCircleRec({circle_x, circle_y}, circle_radius, {axe_x, axe_y, axe_length, axe_length}) && !powerup_active)
        {
            lives--;
            if (lives <= 0)
            {
                game_over = true;
            }
            else
            {
                // Move the player to the center
                circle_x = (Width / 2) - 50;
                circle_y = (Height / 2) - 50;
            }
        }

        if (game_over)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            // Draw the shapes
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);
            DrawCircle(powerup_x, powerup_y, powerup_radius, GREEN);

            // Move the axe randomly
            axe_x += direction_x;
            axe_y += direction_y;

            // Check if axe hits window boundaries, then change direction
            if (axe_x > Width - axe_length || axe_x < 0)
            {
                direction_x = -direction_x + (rand() % 5) - 2; // Change horizontal direction randomly
            }
            if (axe_y > Height - axe_length || axe_y < 0)
            {
                direction_y = -direction_y + (rand() % 5) - 2; // Change vertical direction randomly
            }

            // Circle/Player Movement
            if (IsKeyDown(KEY_D) && circle_x < Width - circle_radius) // move right
            {
                circle_x += 10;
            }

            if (IsKeyDown(KEY_A) && circle_x > circle_radius) // move left
            {
                circle_x -= 10;
            }

            if (IsKeyDown(KEY_W) && circle_y > circle_radius) // move up
            {
                circle_y -= 10;
            }

            if (IsKeyDown(KEY_S) && circle_y < Height - circle_radius) // move down
            {
                circle_y += 10;
            }

            // Power-up logic
            if (CheckCollisionCircles({circle_x, circle_y}, circle_radius, {powerup_x, powerup_y}, powerup_radius))
            {
                powerup_active = true;
                powerup_timer = 5.0f;
                powerup_x = -100; // Move power-up off-screen
                powerup_y = -100;
            }

            if (powerup_active)
            {
                powerup_timer -= GetFrameTime();
                if (powerup_timer <= 0)
                {
                    powerup_active = false;
                    // Generate a new power-up position
                    powerup_x = (rand() % (Width - (int)(2 * powerup_radius))) + powerup_radius;
                    powerup_y = (rand() % (Height - (int)(2 * powerup_radius))) + powerup_radius;
                }
            }

            // Update and display score
            score += GetFrameTime() * 100;
            DrawText(TextFormat("Score: %d", (int)score), 10, 10, 20, BLACK);

            // Display lives
            DrawText(TextFormat("Lives: %d", lives), Width - 100, 10, 20, BLACK);
        }

        // Game logic ends
        EndDrawing();
    }

    CloseWindow();

    return 0;
}






























/*
#include "raylib.h"
#include <ctime>    // For seeding the random number generator
#include <cstdlib>  // For rand() and srand()

int main()
{
    // Window Size
    int Width = 800;
    int Heighth = 450;

    // Circle Details
    float circle_radius = 25;
    float circle_x = (Width/2) - 50;
    float circle_y = (Heighth/2) - 50;

    // Axe Details
    float axe_length = 50;
    float axe_x = 400;
    float axe_y = 0;
    float direction_x = 10;
    float direction_y = 10;

    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    InitWindow(Width, Heighth, "Richard's Window");
    SetTargetFPS(60);

    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE); // prevents flickering 

        // Game logic begins

        // Check for collision
        if(CheckCollisionCircleRec({circle_x, circle_y}, circle_radius, {axe_x, axe_y, axe_length, axe_length}))
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            // Draw the shapes
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            // Move the axe randomly
            axe_x += direction_x;
            axe_y += direction_y;

            // Check if axe hits window boundaries, then change direction
            if(axe_x > Width - axe_length || axe_x < 0) 
            {
                direction_x = -direction_x + (rand() % 5) - 2; // Change horizontal direction randomly
            }
            if(axe_y > Heighth - axe_length || axe_y < 0) 
            {
                direction_y = -direction_y + (rand() % 5) - 2; // Change vertical direction randomly
            }

            // Circle/Player Movement
            if (IsKeyDown(KEY_D) && circle_x < Width - circle_radius) // move right
            {
                circle_x += 10;
            }

            if (IsKeyDown(KEY_A) && circle_x > circle_radius) // move left
            {
                circle_x -= 10;
            }

            // New vertical movement controls
            if (IsKeyDown(KEY_W) && circle_y > circle_radius) // move up
            {
                circle_y -= 10;
            }

            if (IsKeyDown(KEY_S) && circle_y < Heighth - circle_radius) // move down
            {
                circle_y += 10;
            }
        }

        // Game logic ends
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
*/