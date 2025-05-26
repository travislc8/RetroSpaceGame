#include "Game.h"
#include "raylib.h"

int main() {
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Raylib Test");
    SetTargetFPS(60);
    ToggleFullscreen();
    HideCursor();

    Game* game = new Game();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        game->Draw();
        EndDrawing();
    }

    delete game;
    CloseWindow();
}
