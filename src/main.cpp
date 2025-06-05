#include "Game.h"
#include "raylib.h"
#include <stdio.h>

int main() {
    // InitWindow(GetScreenWidth(), GetScreenHeight(), "Raylib Test");
    InitWindow(800, 600, "Raylib Test");
    SetTargetFPS(60);
    // ToggleFullscreen();
    HideCursor();
    // std::cout << "test" << std::endl;
    fprintf(stderr, "test");

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
