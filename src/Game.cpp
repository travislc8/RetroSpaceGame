#include "Game.h"
#include "Bullets.h"
#include "levels/TestLevel.h"
#include "raylib.h"

Game::Game() {
    planeVec.x = 800;
    planeVec.y = 700;
    plane = new Plane(GetScreenWidth(), GetScreenHeight());
    level = Levels::TestLevel();
}

Game::~Game() { delete plane; }

void Game::Draw() {
    KeyInput();
    bullets.Update();
    bullets.Draw();
    plane->Draw();
    level.Update();
    level.Draw();
}

void Game::KeyInput() {
    if (IsKeyPressed(KEY_SPACE)) {
        bullets.Add(plane->GetLocation());
    }

    if (IsKeyDown(KEY_RIGHT)) {
        plane->Move(GetFrameTime() * MOVESPEED);
    } else if (IsKeyDown(KEY_LEFT)) {
        plane->Move(GetFrameTime() * MOVESPEED * -1);
    }
}

// 60x50
void Game::DrawPlane() {
    DrawRectangle(planeVec.x - 12, planeVec.y + 34, 8, 12, RED);
    DrawRectangle(planeVec.x + 6, planeVec.y + 34, 8, 12, RED);

    // body
    DrawRectangle(planeVec.x - 2, planeVec.y + 0, 4, 10, WHITE);
    DrawRectangle(planeVec.x - 6, planeVec.y + 10, 12, 10, WHITE);
    DrawRectangle(planeVec.x - 10, planeVec.y + 20, 20, 14, WHITE);
    DrawRectangle(planeVec.x - 6, planeVec.y + 34, 12, 10, WHITE);
    DrawRectangle(planeVec.x - 2, planeVec.y + 44, 4, 10, WHITE);

    // wings
    DrawRectangle(planeVec.x - 14, planeVec.y + 24, 4, 14, WHITE);
    DrawRectangle(planeVec.x - 18, planeVec.y + 28, 4, 10, WHITE);
    DrawRectangle(planeVec.x - 22, planeVec.y + 32, 4, 10, WHITE);
    DrawRectangle(planeVec.x - 26, planeVec.y + 36, 4, 10, WHITE);
    DrawRectangle(planeVec.x - 30, planeVec.y + 40, 4, 10, WHITE);

    DrawRectangle(planeVec.x + 10, planeVec.y + 24, 4, 14, WHITE);
    DrawRectangle(planeVec.x + 14, planeVec.y + 28, 4, 10, WHITE);
    DrawRectangle(planeVec.x + 18, planeVec.y + 32, 4, 10, WHITE);
    DrawRectangle(planeVec.x + 22, planeVec.y + 36, 4, 10, WHITE);
    DrawRectangle(planeVec.x + 26, planeVec.y + 40, 4, 10, WHITE);

    // cockpit
    DrawRectangle(planeVec.x - 2, planeVec.y + 20, 4, 8, RED);
    DrawRectangle(planeVec.x - 6, planeVec.y + 24, 4, 8, RED);
    DrawRectangle(planeVec.x + 2, planeVec.y + 24, 4, 8, RED);

    // blue dots
    DrawRectangle(planeVec.x - 14, planeVec.y + 20, 4, 4, BLUE);
    DrawRectangle(planeVec.x + 10, planeVec.y + 20, 4, 4, BLUE);

    DrawRectangle(planeVec.x - 18, planeVec.y + 24, 4, 4, BLUE);
    DrawRectangle(planeVec.x + 14, planeVec.y + 24, 4, 4, BLUE);

    // guns
    DrawRectangle(planeVec.x - 18, planeVec.y + 16, 4, 8, WHITE);
    DrawRectangle(planeVec.x + 14, planeVec.y + 16, 4, 8, WHITE);
    DrawRectangle(planeVec.x - 18, planeVec.y + 10, 4, 6, RED);
    DrawRectangle(planeVec.x + 14, planeVec.y + 10, 4, 6, RED);

    DrawRectangle(planeVec.x - 30, planeVec.y + 28, 4, 12, WHITE);
    DrawRectangle(planeVec.x + 26, planeVec.y + 28, 4, 12, WHITE);
    DrawRectangle(planeVec.x - 30, planeVec.y + 22, 4, 6, RED);
    DrawRectangle(planeVec.x + 26, planeVec.y + 22, 4, 6, RED);
}
