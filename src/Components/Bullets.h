#ifndef _BULLETS_H_
#define _BULLETS_H_
#include "Bullet.h"
#include "raylib.h"
#include <list>

namespace Components {

class Bullets {
  private:
    std::list<Bullet*> bullets;
    double lastShot;

  public:
    Bullets();
    ~Bullets();
    void Update();
    void Draw();
    void Add(Vector2);
    std::list<Bullet*> GetBullets();
    void Remove(Bullet*);
};
} // namespace Components
#endif
