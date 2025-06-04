#include "TestLevel.h"
#include "../Components/Enemy.h"
#include "LevelUtils.h"
#include "raylib.h"
#include <vector>

using namespace Levels;
TestLevel::TestLevel() {
    maxGridX = GetScreenWidth() - 50 - (rowCount * ENEMYSPACING);
    minGridX = 0 + 50.0f;
    gridState = LocationInGrid{0, 0, minGridX, 50.0f};
    gridVector = Vector2{minGridX, 50.0f};
    startTime = GetTime();
    lastShiftTime = GetTime();
    SetEnemyEntryPath();
    /*
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < rowCount; j++) {
            Components::Enemy* enemy =
                new Components::Enemy(LocationInGrid{j, i, gridVector.x, gridVector.y},
                                      Vector2{(float)ENEMYSPACING * j, (float)ENEMYSPACING * i});
            enemy->SetLocation(Vector2{0, 0});
            enemyList.push_back(enemy);
        }
    }
    */
    Components::Enemy* enemy =
        new Components::Enemy(gridState, Vector2{(float)(ENEMYSPACING * gridState.column),
                                                 (float)(ENEMYSPACING * gridState.row)});
    enemy->SetEntryPath(enemyEntryPath);
    enemy->SetLocation(Vector2{0, 0});
    enemyList.push_back(enemy);
    gridState.x += ENEMYSPACING;
    gridState.column += 1;
    lastSpawnTime = GetTime();
}

TestLevel::~TestLevel() {
    /*
    for (auto point : enemyEntryPath) {
        delete point;
    }
    enemyEntryPath.clear();
    */
}

void TestLevel::Draw() {
    for (auto enemy : enemyList) {
        enemy->Draw();
    }
}

void TestLevel::Update() {
    if (GetTime() - lastSpawnTime > 0.5f) {
        if (gridState.column > 8) {
            gridState.column = 0;
            gridState.row += 1;
            gridState.y += ENEMYSPACING;
            gridState.x = gridVector.x;
        }
        if (gridState.row < 3) {
            Components::Enemy* enemy =
                new Components::Enemy(gridState, Vector2{(float)(ENEMYSPACING * gridState.column),
                                                         (float)(ENEMYSPACING * gridState.row)});
            enemy->SetEntryPath(enemyEntryPath);
            enemy->SetLocation(Vector2{0, 0});
            enemyList.push_back(enemy);
            gridState.x += ENEMYSPACING;
            gridState.column += 1;
            lastSpawnTime = GetTime();
        }
    }
    if ((GetTime() - lastShiftTime) > .5f) {
        lastShiftTime = GetTime();
        UpdateGridPosition();
        ShiftEnemy();
    }
    for (auto it = enemyList.begin(); it != enemyList.end();) {
        if ((*it)->ShouldDestroy()) {
            delete *it;
            it = enemyList.erase(it);
        } else {
            (*it)->Update();
            it++;
        }
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
    vec.push_back(Vector2{200, 200});
    vec.push_back(Vector2{300, 300});
    vec.push_back(Vector2{400, 400});
    /*
    vec.push_back(Vector2{500, 300});
    vec.push_back(Vector2{400, 200});
    vec.push_back(Vector2{300, 300});
    vec.push_back(Vector2{400, 400});
    vec.push_back(Vector2{500, 300});
    vec.push_back(Vector2{400, 200});
    vec.push_back(Vector2{300, 300});
    vec.push_back(Vector2{400, 400});
    vec.push_back(Vector2{500, 300});
    vec.push_back(Vector2{400, 200});
    vec.push_back(Vector2{300, 300});
    */
    enemyEntryPath = new Logic::Path(vec);
}
