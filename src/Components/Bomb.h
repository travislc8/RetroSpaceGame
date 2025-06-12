#ifndef BOMB_H_
#define BOMB_H_

#include "raylib.h"
#define BOMBSPEED 240

namespace Components {
class Bomb {
  private:
    bool destroy = false;

  public:
    Bomb(Vector2);
    Rectangle hitbox;
    void Draw();
    void Update();
    void SetDestroy() { destroy = true; };
    bool ShouldDestroy() { return destroy; };
    Vector2 GetCorner(int);
};
} // namespace Components

#endif
