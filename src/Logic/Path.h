#ifndef PATH_H_
#define PATH_H_

#include "raylib.h"
#include <vector>

namespace Logic {
class Path {
  private:
    std::vector<Vector2> points;

  public:
    Path();
    Path(std::vector<Vector2>);
    Vector2 GetPoint(int);
    int GetTargetPoint(Vector2, Vector2, int);
    Vector2 GetDirection(Vector2, int);
    void ShowPath();
    Vector2 GetMoveLocation(Vector2, int&, int);
    void SetPath(std::vector<Vector2> points) { this->points = points; };
};

} // namespace Logic
#endif
