#ifndef _TESTLEVEL_H_
#define _TESTLEVEL_H_

#include "../Components/Bombs.h"
#include "../Components/Enemy.h"
#include "../Logic/EnemyType.h"
#include "../Logic/Path.h"
#include "LevelUtils.h"
#include "raylib.h"
#include <list>
#include <memory>
#include <vector>

#define ENEMYSPACING 40
#define GRIDSHIFTSPEED 24

namespace Levels {

enum LevelState {
    LOADING,
    ENEMYENTRY,
    ENEMYATTACKING,
    COMPLETE,
    ENEMYINGRID,
};

class TestLevel {
  private:
    bool gameOver = false;
    int gridDirection = 1; // direction the grid if shifting
    int rowCount = 4;
    int columnCount = 16;
    int maxEnemyAttacking = 3;
    int maxBombs = 2;
    int spawnCount = 0; // how many enemy have been spawned
    int bombChance = 10;
    int attackChance = 128;
    LevelState state = LOADING; // which state the level is in

    float minGridX, maxGridX;
    float levelHeight, levelWidth;
    LocationInGrid gridState;
    Vector2 gridVector; // the top right corner of the grid
    double startTime;
    double lastShiftTime;
    double lastSpawnTime;

    std::list<Components::Enemy*> enemyList;
    std::vector<Components::Enemy*> movingEnemy;

    Logic::Path enemyEntryPath;
    Logic::Path enemyEntryPath2;
    Components::Bombs bombs;

    /**
     * Shifts the each individual enemies grid location by the same amount
     */
    void ShiftEnemy();
    /**
     * Updates the grid location so that it shifts a small amount at time intervals
     */
    void UpdateGridPosition();
    /**
     * Sets the entry paths that can be used in the level
     */
    void SetEnemyEntryPath();
    /**
     * Adds a new enemy of the specified type with the given physics
     */
    void AddEnemy(std::shared_ptr<Logic::Physics>, Logic::EnemyType);
    /**
     * Sets the enemy for the level
     */
    void SetEnemy();
    /**
     * Creates an attack with a random enemy
     */
    void CreateAttack();
    void EnemyEntryState();
    void LevelCompleteState();
    void EnemyInGridState();
    void EnemyAttackingState();

  public:
    TestLevel(float, float);
    ~TestLevel();
    void Update();
    void Draw();
    std::list<Components::Enemy*> GetEnemyList() { return enemyList; }
    std::list<Components::Bomb*> GetBombList() { return bombs.GetBombs(); }
    void Remove(Components::Enemy*);
    void EndGame();
};

} // namespace Levels

#endif
