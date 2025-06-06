#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "raylib.h"

#define STARCOUNT 100
namespace Components {

class Background {
  private:
    Vector2 stars1[STARCOUNT];
    Vector2 stars2[STARCOUNT];
    double lastRedraw;
    short state = 0;

  public:
    Background(float, float);
    void Draw();
};
} // namespace Components
#endif
