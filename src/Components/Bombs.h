#ifndef _BOMBS_H_
#define _BOMBS_H_
#include "Bomb.h"
#include "raylib.h"
#include <list>

namespace Components {

class Bombs {
  private:
    std::list<Bomb*> bombs;
    double lastShot;
    int maxY = 1000;

  public:
    Bombs();
    ~Bombs();
    void Update();
    void Draw();
    void Add(Vector2);
    std::list<Bomb*> GetBombs();
    void Remove(Bomb*);
    int Size() { return bombs.size(); };
    void SetGround(int x) { maxY = x; };
};
} // namespace Components
#endif
