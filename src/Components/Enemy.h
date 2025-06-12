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
    // private:
  protected:
    int gameWidth = 900, gameHeight = 700;
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
    bool hasDropedBomb = false;
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
    virtual void UpdateAttackPath() = 0;

    Texture2D images[2];

  public:
    virtual void LoadTexture() = 0;
    Rectangle hitbox;

    Enemy(Levels::LocationInGrid, Vector2);
    virtual ~Enemy();
    Vector2 GetLocation() { return location; };
    void SetLocation(Vector2);
    virtual void Draw() = 0;
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
    bool HasDropedBomb() { return hasDropedBomb; };
    void SetHasDropedBomb(bool var) { hasDropedBomb = var; };
    void SetGameSize(int, int);
};
} // namespace Components

#endif
