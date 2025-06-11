#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../Levels/LevelUtils.h"
#include "../Logic/Mode.h"
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
    Logic::EnemyMode mode;
    Levels::LocationInGrid gridLocation;
    Vector2 offset;
    Logic::Path entryPath;
    float spawnTime;
    float imageTime;
    int imageIndex = 0;
    Rectangle src;
    Rectangle dest;
    Vector2 origin;
    Logic::Path attackPath;

    float GetGridLocationX();
    float GetGridLocationY();
    void LocateInGrid();

    void EntryMode();
    void ReturnToGridMode();
    void NotSpawnedMode();
    void AttackMode();
    void MoveAmount(Vector2);
    void MoveTo(Vector2);
    void InitAttackPath();
    float GetMoveAngleSmooth(float, float);

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
    void SetEntryPath(Logic::Path);
    void SetPhysics(std::shared_ptr<Logic::Physics> physics) { this->physics = physics; };
    void Spawn();
    void SetSpawnTime(float time);
    Vector2 GetCorner(int);
    void MakeAttack();
    void SetInGrid();
};
} // namespace Components

#endif
