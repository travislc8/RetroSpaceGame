#ifndef _BULLET_H_
#define _BULLET_H_
#include "raylib.h"
namespace Components {
const int BULLETSPEED = 720;
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
