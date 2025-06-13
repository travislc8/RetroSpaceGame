#include "Game.h"
#include "draw.h"
#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

void main_test() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Test");

    SetTargetFPS(60);

    int xdir = 1;
    int ydir = 1;
    int max_x = 2000;
    int max_y = 1000;

    Rectangle player = {400, 280, 40, 40};
    Camera2D camera = {0};
    camera.target = (Vector2){player.x + 20.0f, player.y + 20.0f};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    circle* c = new circle{Vector2{50, 50}, 1, 1};
    auto vec = std::vector<circle*>();
    vec.push_back(c);

    Game* game = new Game();
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        // Player movement
        if (IsKeyDown(KEY_S))
            player.y += 2;
        else if (IsKeyDown(KEY_W))
            player.y -= 2;

        if (IsKeyDown(KEY_D))
            player.x += 2;
        else if (IsKeyDown(KEY_A))
            player.x -= 2;

        // Camera target follows player
        camera.target = (Vector2){player.x + 20, player.y + 20};

        // Camera rotation controls
        if (IsKeyDown(KEY_E))
            camera.rotation--;
        else if (IsKeyDown(KEY_Q))
            camera.rotation++;

        // Camera zoom controls
        // Uses log scaling to provide consistent zoom speed
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));

        if (camera.zoom > 3.0f)
            camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f)
            camera.zoom = 0.1f;
        // Camera reset (zoom and rotation)
        if (IsKeyPressed(KEY_R)) {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }
        // Camera reset (zoom and rotation)
        if (IsKeyPressed(KEY_R)) {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }

        // draw
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);
        for (int i = 0; i < max_x; i += 100) {
            for (int j = 0; j < max_y; j += 100) {
                DrawRectangle(i, j, 50, 50, BLUE);
            }
        }
        auto pos = GetScreenToWorld2D(Vector2{(float)GetMouseX(), (float)GetMouseY()}, camera);

        if (IsMouseButtonPressed(0)) {
            vec.push_back(new circle{pos.x, pos.y, xdir, ydir});
            xdir = xdir * ydir;
            ydir = ydir * -1;
        }
        DrawRectangleRec(player, RED);
        Draw(vec, max_y, max_x);
        EndMode2D();

        EndDrawing();
    }

    delete c;
    delete game;
}
