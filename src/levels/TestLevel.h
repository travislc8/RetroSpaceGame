#ifndef _TESTLEVEL_H_
#define _TESTLEVEL_H_

#include "../Enemy.h"
#include "raylib.h"
#include <list>

namespace Levels {

class TestLevel {
  private:
    double startTime;
    std::list<Enemy> enemyList;

  public:
    TestLevel();
    void Update();
    void Draw();
};

} // namespace Levels

#endif
