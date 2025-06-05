#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../Levels/LevelUtils.h"
#include "../Logic/Path.h"
#include "raylib.h"
#include <vector>

#define ENEMYWIDTH 20
#define ENEMYHEIGHT 20
#define ENEMYSPEED 250
#define TURNSPEED .1f

namespace Components {

class Enemy {
  private:
    Vector2 location;
    Vector2 direction;
    bool destroy = false;
    bool moving = false;
    int state;
    int nextTarget = 0;
    Levels::LocationInGrid gridLocation;
    Vector2 offset;
    Logic::Path* entryPath;
    int pointIndex = 0;

    float GetGridLocationX();
    float GetGridLocationY();
    void LocateInGrid();

    void MoveState0();
    void MoveState2();
    void MoveAmount(Vector2);
    void MoveTo(Vector2);

  public:
    Rectangle hitbox;

    Enemy(Levels::LocationInGrid, Vector2);
    ~Enemy();
    Vector2 GetLocation() { return location; };
    void SetLocation(Vector2);
    void Draw();
    void SetDestroy() { destroy = true; };
    bool ShouldDestroy() { return destroy; };
    bool IsMoving() { return moving; };
    void SetMoving(bool moving) { this->moving = moving; };
    void Update();
    void SetGridLocation(Vector2);
    void SetEntryPath(Logic::Path*);
};
} // namespace Components

#endif
