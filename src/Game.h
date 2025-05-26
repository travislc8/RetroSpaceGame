#ifndef _GAME_H_
#define _GAME_H_
#include "Bullets.h"
#include "Plane.h"
#include "raylib.h"

class Game {
  private:
    Vector2 planeVec;
    Bullets bullets;
    const int MOVESPEED = 250;
    Plane* plane;

  public:
    Game();
    ~Game();
    void Draw();
    void DrawPlane();
    void KeyInput();
};

#endif
