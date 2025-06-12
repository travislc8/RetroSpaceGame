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
    float minGridX, maxGridX;
    float levelHeight, levelWidth;
    LocationInGrid gridState;
    Vector2 gridVector;
    double startTime;
    double lastShiftTime;
    double lastSpawnTime;
    int rowCount = 8;
    int columnCount = 2;
    int maxEnemyAttacking = 2;
    int maxBombs = 2;
    std::list<Components::Enemy*> enemyList;
    Components::Bombs bombs;
    short gridDirection = 1;
    int spawnCount = 0;
    int bombChance = 10;
    int attackChance = 128;
    std::vector<Components::Enemy*> movingEnemy;
    LevelState state = LOADING;

    Logic::Path enemyEntryPath;
    Logic::Path enemyEntryPath2;

    void ShiftEnemy();
    void UpdateGridPosition();
    void SetEnemyEntryPath();
    void AddEnemy(std::shared_ptr<Logic::Physics>, Logic::EnemyType);
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
    std::list<Components::Bomb*> GetBombList() { return bombs.GetBombs(); }
    void Remove(Components::Enemy*);
    void EndGame();
};

} // namespace Levels

#endif
