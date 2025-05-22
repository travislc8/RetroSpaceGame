#ifndef _DRAW_H_
#define _DRAW_H_
#include <vector>
struct circle {
  int x = 50;
  int y = 50;
  int xdir = 1;
  int ydir = 1;
};

void Draw(std::vector<circle *>, int, int);

#endif
