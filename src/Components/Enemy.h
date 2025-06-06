#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../Levels/LevelUtils.h"
#include "../Logic/Path.h"
#include "../Logic/Physics.h"
#include "raylib.h"
#include <cstdio>
#include <memory>
#include <vector>

#define ENEMYWIDTH 30
#define ENEMYHEIGHT 30

namespace Components {

class Enemy {
  private:
    Texture2D butterfly1;
    Texture2D butterfly2;
    Texture2D images[2];
    std::shared_ptr<Logic::Physics> physics;
    Vector2 location;
    Vector2 direction;
    bool destroy = false;
    bool moving = false;
    int state;
    int nextTarget = 0;
    Levels::LocationInGrid gridLocation;
    Vector2 offset;
    std::shared_ptr<Logic::Path> entryPath;
    int pointIndex = 0;
    float spawnTime;
    float imageTime;
    int imageIndex = 0;
    Rectangle src;
    Rectangle dest;
    Vector2 origin;

    float GetGridLocationX();
    float GetGridLocationY();
    void LocateInGrid();

    void MoveState0();
    void MoveState2();
    void MoveState3();
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
    void SetEntryPath(std::shared_ptr<Logic::Path>);
    void SetPhysics(std::shared_ptr<Logic::Physics> physics) { this->physics = physics; };
    void Spawn();
    void SetSpawnTime(float time);
};
} // namespace Components

#endif
