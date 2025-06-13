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

    Game* game = new Game();
    game->Run();

    delete game;
    CloseWindow();
}
