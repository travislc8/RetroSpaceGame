#include "draw.h"
#include "raylib.h"
#include <iostream>
#include <vector>
int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Raylib Test");

  SetTargetFPS(60);

  int xdir = 1;
  int ydir = 1;
  circle *c = new circle{50, 50, 1, 1};
  auto vec = std::vector<circle *>();
  vec.push_back(c);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    if (IsMouseButtonPressed(0)) {
      vec.push_back(new circle{GetMouseX(), GetMouseY(), xdir, ydir});
      xdir = xdir * ydir;
      ydir = ydir * -1;
    }
    Draw(vec, screenHeight, screenWidth);
    EndDrawing();
  }

  delete c;
}
