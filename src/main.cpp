#include "Debug.h"
#include "Game.h"
#include "raylib.h"
#include <stdio.h>

int main() {
    PRINT(0, fprintf(stderr, "\ntest"));
    // InitWindow(GetScreenWidth(), GetScreenHeight(), "Raylib Test");
    InitWindow(1200, 700, "Raylib Test");
    SetTargetFPS(60);
    // ToggleFullscreen();
    HideCursor();

    SetRandomSeed(GetTime());
    Game* game = new Game();
    while (!WindowShouldClose()) {
        if (!IsKeyPressed(KEY_P)) {
            BeginDrawing();
            ClearBackground(BLACK);
            game->Update();
            game->Draw();
            EndDrawing();
        }
    }

    delete game;
    CloseWindow();
}
