#include "Game.h"



int main() {
    
    // Initialize the window
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Inventory System");

    Game game;
    // Load background texture
    Texture2D bg = LoadTexture("Assets/nbg.png");


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
        DrawText(std::to_string(GetFPS()).c_str(),20,25,20,BLACK);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}