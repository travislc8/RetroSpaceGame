#include "TestLevel.h"
#include "raylib.h"

Levels::TestLevel::TestLevel() { enemyList.push_back(Enemy()); }

void Levels::TestLevel::Draw() {
    for (auto enemy : enemyList) {
        enemy.Draw();
    }
}

void Levels::TestLevel::Update() {}
