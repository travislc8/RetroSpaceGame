#include "draw.h"
#include "raylib.h"

void Draw(std::vector<circle *> vec, int h, int w) {
  DrawText("hello", 100, 100, 20, BLACK);

  for (circle *c : vec) {
    c->x += 4 * c->xdir;
    c->y += 4 * c->ydir;

    if (c->x > w) {
      c->xdir = -1;
    } else if (c->x < 0) {
      c->xdir = 1;
    }
    if (c->y > h) {
      c->ydir = -1;
    } else if (c->y < 0) {
      c->ydir = 1;
    }
    DrawCircle(c->x, c->y, 10, RED);
  }
}
