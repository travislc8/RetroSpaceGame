#ifndef _DRAW_H_
#define _DRAW_H_
#include "raylib.h"
#include <vector>
struct circle {
  Vector2 vec = {50, 50};
  int xdir = 1;
  int ydir = 1;
};

void Draw(std::vector<circle *>, int, int);

#endif
