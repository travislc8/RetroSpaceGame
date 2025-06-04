#ifndef _GAME_H_
#define _GAME_H_
#include "Components/Background.h"
#include "Components/Bullets.h"
#include "Components/Plane.h"
#include "Levels/TestLevel.h"
#include "raylib.h"

#define MOVESPEED 250
class Game {
  private:
    Vector2 planeVec;
    Components::Bullets bullets;
    Components::Plane* plane;
    Levels::TestLevel level;
    Components::Background background;

    void DrawPlane();
    void KeyInput();
    void CheckBullets();
    void CheckBombs();

  public:
    Game();
    ~Game();
    void Update();
    void Draw();
};

#endif
