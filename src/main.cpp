#include "../include/raylib.h"
int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Raylib Test");

  SetTargetFPS(60);

  int x = 50;
  int y = 50;
  int xdir = 1;
  int ydir = 1;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("hello", 100, 100, 20, BLACK);

    x += 5 * xdir;
    y += 5 * ydir;

    if (x > screenWidth) {
      xdir = -1;
    } else if (x < 0) {
      xdir = 1;
    }
    if (y > screenHeight) {
      ydir = -1;
    } else if (y < 0) {
      ydir = 1;
    }
    DrawCircle(x, y, 10, RED);
    EndDrawing();
  }
}
