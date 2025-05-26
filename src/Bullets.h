#ifndef _BULLETS_H_
#define _BULLETS_H_
#include "raylib.h"
#include <list>

const int BULLETSPEED = 720;

class Bullets {
  private:
    class Bullet {
      private:
      public:
        Bullet(Vector2);
        Rectangle rect;
        void Update();
    };
    std::list<Bullet*> bullets;
    double lastShot;

  public:
    Bullets();
    ~Bullets();
    void Update();
    void Draw();
    void Add(Vector2);
};
#endif
