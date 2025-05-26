#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "raylib.h"
class Enemy {
  private:
    Vector2 location;
    Rectangle hitbox;

  public:
    Enemy();
    ~Enemy();
    Vector2 GetLocation() { return location; };
    void SetLocation(Vector2);
    void Draw();
    Rectangle GetRect() { return hitbox; };
};

#endif
