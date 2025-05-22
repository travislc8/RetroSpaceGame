#include "draw.h"
#include "raylib.h"

void Draw(std::vector<circle *> vec, int h, int w) {
  DrawText("hello", 100, 100, 20, BLACK);

  for (circle *c : vec) {
    c->vec.x += 4 * c->xdir;
    c->vec.y += 4 * c->ydir;

    if (c->vec.x > w) {
      c->xdir = -1;
    } else if (c->vec.x < 0) {
      c->xdir = 1;
    }
    if (c->vec.y > h) {
      c->ydir = -1;
    } else if (c->vec.y < 0) {
      c->ydir = 1;
    }
    DrawCircle(c->vec.x, c->vec.y, 10, RED);
  }
}
