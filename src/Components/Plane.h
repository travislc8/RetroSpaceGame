#ifndef _PLANE_H_
#define _PLANE_H_
#include "Enemy.h"
#include "raylib.h"
namespace Components {
class Plane {
  private:
    int planeWidth, planeHeight;
    int minX, maxX;
    Vector2* points;
    float angle;
    Texture2D plane;

  public:
    Plane(int, int);
    ~Plane();
    void Move(int);
    void Move(Vector2);
    void Draw();
    Vector2 GetLocation();
};
} // namespace Components

#endif
