#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_
#include "raylib.h"
class Scoreboard {
  private:
    Vector2 origin;
    float width, height;
    int score = 0;
    int lives = 3;
    Texture2D planeTexture;

  public:
    Scoreboard(Vector2, float, float);
    void Draw();
    void Add(int);
    void RemoveLife();
    int GetLives();
    void AddLife();
    void SetLives(int);
};

#endif
