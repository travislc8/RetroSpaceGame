#ifndef _GAME_H_
#define _GAME_H_
#include "Components/Background.h"
#include "Components/Bullets.h"
#include "Components/Plane.h"
#include "Levels/TestLevel.h"
#include "Scoreboard.h"
#include "raylib.h"

#define MOVESPEED 250
#define SCOREBOARDSIZE 300
class Game {
  private:
    Vector2 planeVec;
    Components::Bullets bullets;
    Components::Plane* plane;
    Levels::TestLevel* level;
    Components::Background* background;
    float gameWidth, gameHeight;
    Scoreboard* scoreboard;

    void DrawPlane();
    void KeyInput();
    void CheckBullets();
    void CheckBombs();
    void CheckCollisions();

  public:
    Game();
    ~Game();
    void Update();
    void Draw();
};

#endif
