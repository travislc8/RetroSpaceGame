#ifndef PATH_H_
#define PATH_H_

#include "raylib.h"
#include <stdio.h>
#include <vector>

namespace Logic {
class Path {
  private:
    std::vector<Vector2> points;
    int pointIndex = 0;
    void UpdateTargetIndex(Vector2, Vector2, float);

  public:
    Path();
    Path(std::vector<Vector2>);
    Vector2 GetPoint();
    void UpdatePoint(Vector2, Vector2, float);
    Vector2 GetDirection(Vector2);
    void ShowPath();
    Vector2 GetMoveLocation(Vector2, int);
    void SetPath(std::vector<Vector2> points) { this->points = points; };
    bool IsComplete();
    void Reset();
};

} // namespace Logic
#endif
