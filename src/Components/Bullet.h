#ifndef _BULLET_H_
#define _BULLET_H_
#include "raylib.h"

#define BULLETSPEED 720
namespace Components {
class Bullet {
  private:
    bool destroy = false;

  public:
    Bullet(Vector2);
    Rectangle hitbox;
    void Draw();
    void Update();
    void SetDestroy() { destroy = true; };
    bool ShouldDestroy() { return destroy; };
};

} // namespace Components
#endif
