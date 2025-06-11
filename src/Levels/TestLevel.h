#ifndef _TESTLEVEL_H_
#define _TESTLEVEL_H_

#include "../Components/Enemy.h"
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
    float minGridX, maxGridX;
    float levelHeight, levelWidth;
    LocationInGrid gridState;
    Vector2 gridVector;
    double startTime;
    double lastShiftTime;
    double lastSpawnTime;
    int rowCount = 8;
    int columnCount = 2;
    std::list<Components::Enemy*> enemyList;
    short gridDirection = 1;
    int spawnCount = 0;
    int movingEnemyCount = 0;
    LevelState state = LOADING;
    float timeInEnemyInGrid;

    Logic::Path enemyEntryPath;
    Logic::Path enemyEntryPath2;

    void ShiftEnemy();
    void UpdateGridPosition();
    void SetEnemyEntryPath();
    void AddEnemy(std::shared_ptr<Logic::Physics>);
    void SetEnemy();
    void SpawnEnemy();
    void EnemyEntryState();
    void LevelCompleteState();
    void EnemyInGridState();
    void EnemyAttackingState();

    void CreateAttack();

  public:
    TestLevel(float, float);
    ~TestLevel();
    void Update();
    void Draw();
    std::list<Components::Enemy*> GetEnemyList() { return enemyList; }
    void Remove(Components::Enemy*);
};

} // namespace Levels

#endif
