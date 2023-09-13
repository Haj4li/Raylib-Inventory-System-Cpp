#include "Game.h"
#include <random>


int main() {
    
    // Initialize the window
    InitWindow(800,600,"Sprite2D | Subscribe please -");

    Game game;
    // Load background texture
    Texture2D bg = LoadTexture("Assets/BG.png");


    // Random numbers
    std::random_device rd;  // Seed generator from hardware or system
    std::mt19937 mt(rd()); // Mersenne Twister engine

    // We need to make sure that the random position is visible in the screen x  and y
    std::uniform_int_distribution<int> distx(50, 750);
    std::uniform_int_distribution<int> disty(50, 550);


    SetTargetFPS(60);
    game.Start();

    while (!WindowShouldClose())
    {
        // Update   
        game.Update();
        

        // Draw
        BeginDrawing();

        ClearBackground(WHITE);

        // Draw Background
        DrawTexture(bg,0,0,WHITE);

        game.Draw();

        std::string mpos = std::to_string(GetMouseX()) + " : " + std::to_string(GetMouseY());
        DrawText(mpos.c_str(),15,15,15,BLACK);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}