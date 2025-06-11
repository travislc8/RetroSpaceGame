#include "TestLevel.h"
#include "../Components/Enemy.h"
#include "LevelUtils.h"
#include "raylib.h"
#include <iterator>
#include <memory>
#include <vector>

using namespace Levels;
TestLevel::TestLevel(float width, float height) {
#if MODE == 1
    fprintf(stderr, "\nTestLevelStart");
#endif
    levelWidth = width;
    levelHeight = height;
    maxGridX = width - 50 - (rowCount * ENEMYSPACING);
    minGridX = 0 + 50.0f;
    gridState = LocationInGrid{0, 0, minGridX, 50.0f};
    gridVector = Vector2{minGridX, 50.0f};
    startTime = GetTime();
    lastShiftTime = GetTime();
    SetEnemyEntryPath();
    SetEnemy();
    lastSpawnTime = GetTime();

#if MODE == 1
    fprintf(stderr, "\nTestLevel End");
#endif

    state = LevelState::ENEMYENTRY;
}

TestLevel::~TestLevel() {
    for (auto enemy : enemyList) {
        delete enemy;
    }
    enemyList.clear();
}

void TestLevel::Draw() {
    for (auto enemy : enemyList) {
        enemy->Draw();
    }
}

void TestLevel::Remove(Components::Enemy* renemy) {
    for (auto lenemy : enemyList) {
        if (renemy == lenemy) {
            lenemy->SetDestroy();
            break;
        }
    }
}

void TestLevel::ShiftEnemy() {
    for (auto enemy : enemyList) {
        enemy->SetGridLocation(gridVector);
    }
}

void TestLevel::UpdateGridPosition() {
    gridVector.x += (gridDirection * GRIDSHIFTSPEED);
    if (gridVector.x < minGridX) {
        gridVector.x = minGridX;
        gridDirection *= -1;
    } else if (gridVector.x > maxGridX) {
        gridVector.x = maxGridX;
        gridDirection *= -1;
    }
    gridState.x = gridVector.x;
}

void TestLevel::SetEnemyEntryPath() {
    std::vector<Vector2> vec;
    vec.push_back(Vector2{100, 100});
    vec.push_back(Vector2{400, 400});
    vec.push_back(Vector2{401, 640});
    enemyEntryPath.SetPath(vec);

    std::vector<Vector2> vec2;
    vec2.push_back(Vector2{130, 70});
    vec2.push_back(Vector2{430, 370});
    vec2.push_back(Vector2{431, 600});

    enemyEntryPath2.SetPath(vec2);
}

void TestLevel::AddEnemy(std::shared_ptr<Logic::Physics> physics) {
    Components::Enemy* enemy =
        new Components::Enemy(gridState, Vector2{(float)(ENEMYSPACING * gridState.column),
                                                 (float)(ENEMYSPACING * gridState.row)});
    if (spawnCount % 2 == 0) {
        enemy->SetEntryPath(enemyEntryPath);
        enemy->SetLocation(Vector2{0, 20});
        enemy->SetSpawnTime(GetTime() + (1 + (spawnCount++ * .2f)));
    } else {
        enemy->SetEntryPath(enemyEntryPath2);
        enemy->SetLocation(Vector2{20, 0});
        enemy->SetSpawnTime(GetTime() + (1 + ((spawnCount++ - 1) * .2f)));
    }
    enemy->SetPhysics(physics);
    enemyList.push_back(enemy);
    gridState.x += ENEMYSPACING;
    gridState.column += 1;

    // fprintf(stderr, "\nspeed: %d", physics->GetSpeed());
}

void TestLevel::SetEnemy() {
    std::shared_ptr<Logic::Physics> physics = std::make_shared<Logic::Physics>();
    physics->SetSpeed(250);
    physics->SetTurnSpeed(.2f);
    AddEnemy(physics);

    while (gridState.row < 3) {
        AddEnemy(physics);
        if (gridState.column > 8) {
            gridState.column = 0;
            gridState.row += 1;
            gridState.y += ENEMYSPACING;
            gridState.x = gridVector.x;
        }
    }
}

void TestLevel::Update() {
#if MODE == 2 || MODE == 1
    if (IsKeyPressed(KEY_K)) {
        enemyList.front()->SetDestroy();
    }
    if (IsKeyPressed(KEY_G)) {
        timeInEnemyInGrid = GetTime();
        state = LevelState::ENEMYINGRID;
        for (auto it : enemyList) {
            (*it).SetInGrid();
        }
    }
#endif
    if (enemyList.size() == 0) {
        state = LevelState::COMPLETE;
    }
    if ((GetTime() - lastShiftTime) > .5f) {
        lastShiftTime = GetTime();
        UpdateGridPosition();
        ShiftEnemy();
    }

    movingEnemyCount = 0;

    for (auto it = enemyList.begin(); it != enemyList.end();) {
        if ((*it)->ShouldDestroy()) {
            delete *it;
            it = enemyList.erase(it);
        } else {
            (*it)->Update();
            if ((*it)->IsMoving()) {
                movingEnemyCount++;
            }
            it++;
        }
    }

    switch (state) {
    case LOADING:
        break;
    case ENEMYENTRY:
        EnemyEntryState();
        break;
    case ENEMYATTACKING:
        EnemyAttackingState();
        break;
    case ENEMYINGRID:
        EnemyInGridState();
        break;
    case COMPLETE:
        LevelCompleteState();
        break;
    }
}

void TestLevel::EnemyEntryState() {
    if (movingEnemyCount == 0) {
        state = LevelState::ENEMYINGRID;
        timeInEnemyInGrid = GetTime();
    }
}
void TestLevel::LevelCompleteState() {
    DrawText("Level Complete", levelWidth / 2 - 100, levelHeight / 2 - 20, 20, WHITE);
}

void TestLevel::EnemyInGridState() {
    fprintf(stderr, "\nTime: %f", GetTime() - timeInEnemyInGrid);
    if (GetTime() - timeInEnemyInGrid > 1.5f) {
        CreateAttack();
        timeInEnemyInGrid = GetTime();
    }
}
void TestLevel::EnemyAttackingState() {
    if (movingEnemyCount == 0) {
        state = LevelState::ENEMYINGRID;
        timeInEnemyInGrid = GetTime();
    }
}

void TestLevel::CreateAttack() {
    state = LevelState::ENEMYATTACKING;
    SetRandomSeed(GetTime());
    if (enemyList.size() > 1) {
        float rand1 = GetRandomValue(0, enemyList.size());
        float rand2 = GetRandomValue(0, enemyList.size());
        while (rand1 == rand2) {
            rand2 = GetRandomValue(0, enemyList.size());
        }

        int index = 0;
        for (auto it : enemyList) {
            if (index == rand1 || index == rand2) {
                (*it).MakeAttack();
            }
            index++;
        }
    } else {
        for (auto it : enemyList) {
            (*it).MakeAttack();
        }
    }
}
