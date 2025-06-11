#ifndef _PLANE_H_
#define _PLANE_H_
#include "Enemy.h"
#include "raylib.h"
namespace Components {
class Plane {
  private:
    int planeWidth, planeHeight;
    int minX, maxX;
    float y;
    Vector2* points;
    float angle;
    Texture2D plane;
    bool destroy = false;

  public:
    Plane(int, int);
    ~Plane();
    void Move(int);
    void Move(Vector2);
    void Draw();
    Vector2 GetLocation();
    Vector2 GetPoint(int);
    void SetDestroy();
    bool ShouldDestroy() { return destroy; };
    void Reset();
    bool IsAlive() { return !destroy; }
};
} // namespace Components

#endif
