#include "TestLevel.h"
#include "../Components/Butterfly.h"
#include "../Components/Crab.h"
#include "../Components/Enemy.h"
#include "../Components/Fly.h"
#include "../Debug.h"
#include "LevelUtils.h"
#include "raylib.h"
#include <iterator>
#include <memory>
#include <vector>

using namespace Levels;
TestLevel::TestLevel(float width, float height) {
    PRINT(0, fprintf(stderr, "\nTestLevelStart"));
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
    bombs.SetGround(height);

    PRINT(2, fprintf(stderr, "\nTestLevel End"));

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
    bombs.Draw();
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

void TestLevel::AddEnemy(std::shared_ptr<Logic::Physics> physics, Logic::EnemyType type) {
    Components::Enemy* enemy;
    switch (type) {
    case Logic::BUTTERFLY:
        enemy =
            new Components::Butterfly(gridState, Vector2{(float)(ENEMYSPACING * gridState.column),
                                                         (float)(ENEMYSPACING * gridState.row)});
        break;
    case Logic::FLY:
        enemy = new Components::Fly(gridState, Vector2{(float)(ENEMYSPACING * gridState.column),
                                                       (float)(ENEMYSPACING * gridState.row)});
        break;
    case Logic::CRAB:
        enemy = new Components::Crab(gridState, Vector2{(float)(ENEMYSPACING * gridState.column),
                                                        (float)(ENEMYSPACING * gridState.row)});
        break;
    }
    enemy->LoadTexture();
    enemy->SetGameSize(levelWidth, levelHeight);
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

    PRINT(2, fprintf(stderr, "\nspeed: %d", physics->GetSpeed()));
}

void TestLevel::SetEnemy() {
    std::shared_ptr<Logic::Physics> physics = std::make_shared<Logic::Physics>();
    physics->SetSpeed(350);
    physics->SetTurnSpeed(.2f);

    while (gridState.row < 5) {
        if (gridState.row == 0) {
            AddEnemy(physics, Logic::CRAB);
        } else if (gridState.row % 2 == 0) {
            AddEnemy(physics, Logic::BUTTERFLY);
        } else if (gridState.row % 2 == 1) {
            AddEnemy(physics, Logic::FLY);
        }
        if (gridState.column > 8) {
            gridState.column = 0;
            gridState.row += 1;
            gridState.y += ENEMYSPACING;
            gridState.x = gridVector.x;
        }
    }
}

void TestLevel::Update() {
    bombs.Update();
#if MODE > 0
    if (IsKeyPressed(KEY_K)) {
        enemyList.front()->SetDestroy();
    }
    if (IsKeyPressed(KEY_G)) {
        state = LevelState::ENEMYINGRID;
        for (auto it : enemyList) {
            (*it).SetInGrid();
        }
    }
    if (IsKeyPressed(KEY_F)) {
        CreateAttack();
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

    movingEnemy.clear();

    for (auto it = enemyList.begin(); it != enemyList.end();) {
        if ((*it)->ShouldDestroy()) {
            delete *it;
            it = enemyList.erase(it);
        } else {
            (*it)->Update();
            if ((*it)->IsMoving()) {
                movingEnemy.push_back((*it));
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
    if (movingEnemy.size() == 0) {
        state = LevelState::ENEMYINGRID;
    }
}
void TestLevel::LevelCompleteState() {
    DrawText("Level Complete", levelWidth / 2 - 100, levelHeight / 2 - 20, 20, WHITE);
}

void TestLevel::EnemyInGridState() {
    if (GetRandomValue(0, attackChance) == 0 && movingEnemy.size() < maxEnemyAttacking) {
        CreateAttack();
    }
}

void TestLevel::EnemyAttackingState() {
    if (GetRandomValue(0, attackChance) == 0 && movingEnemy.size() < maxEnemyAttacking) {
        CreateAttack();
    }

    if (movingEnemy.size() == 0) {
        state = LevelState::ENEMYINGRID;
    }

    if (bombs.Size() < maxBombs) {
        for (auto enemy : movingEnemy) {
            if ((*enemy).GetLocation().y > 300 && (*enemy).GetLocation().y < 350) {
                int rand = GetRandomValue(0, bombChance);
                if (rand == 0 && !(*enemy).HasDropedBomb()) {
                    bombs.Add((*enemy).GetLocation());
                    (*enemy).SetHasDropedBomb(true);
                }
                break;
            }
        }
    }
}

void TestLevel::CreateAttack() {
    state = LevelState::ENEMYATTACKING;
    if (enemyList.size() > 1) {
        float rand1 = GetRandomValue(0, enemyList.size());

        int index = 0;
        for (auto it : enemyList) {
            if (index == rand1) {
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

void TestLevel::EndGame() { gameOver = true; }
