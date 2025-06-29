#include "Enemy.h"
#include "../Debug.h"
#include "../Logic/Path.h"
#include "raylib.h"
#include "raymath.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>

using namespace Components;

Enemy::Enemy(Levels::LocationInGrid gridLocation, Vector2 offset) {
    this->offset = offset;
    this->gridLocation = gridLocation;
    LocateInGrid();
    hitbox = Rectangle{location.x, location.y, ENEMYWIDTH, ENEMYHEIGHT};
    mode = Logic::EnemyMode::NOTSPAWNED;
    direction = Vector2Normalize(Vector2{1, 1});
    moving = true;
    InitAttackPath();
}

Enemy::~Enemy() {
    for (auto texture : images) {
        UnloadTexture(texture);
    };
}

void Enemy::SetLocation(Vector2 location) { MoveTo(location); }

void Enemy::Update() {
    switch (mode) {
    case Logic::EnemyMode::ENTRY:
        EntryMode();
        break;
    case Logic::EnemyMode::INGRID:
        LocateInGrid();
        break;
    case Logic::EnemyMode::RETURNTOGRID:
        ReturnToGridMode();
        break;
    case Logic::EnemyMode::NOTSPAWNED:
        NotSpawnedMode();
        break;
    case Logic::EnemyMode::ATTACK:
        AttackMode();
        break;
    default:
        break;
    }
}

void Enemy::SetGridLocation(Vector2 gridLocation) {
    this->gridLocation.x = gridLocation.x;
    this->gridLocation.y = gridLocation.y;
}

void Enemy::LocateInGrid() {
    this->location.x = gridLocation.x + offset.x;
    this->location.y = gridLocation.y + offset.y;
    hitbox.x = location.x;
    hitbox.y = location.y;

    direction = Vector2{0, -1};
    moving = false;
}

void Enemy::MoveAmount(Vector2 vec) {
    location.x += vec.x * physics->GetSpeed() * GetFrameTime();
    location.y += vec.y * physics->GetSpeed() * GetFrameTime();
    hitbox.x = location.x;
    hitbox.y = location.y;
}

void Enemy::MoveTo(Vector2 vec) {
    this->location.x = vec.x;
    this->location.y = vec.y;
    hitbox.x = location.x;
    hitbox.y = location.y;
}

void Enemy::EntryMode() {
    PRINT(2, fprintf(stderr, "\n Entry"));
    entryPath.UpdatePoint(location, direction, physics->GetSpeed() * GetFrameTime());
    if (entryPath.IsComplete()) {
        mode = Logic::EnemyMode::RETURNTOGRID;
        ReturnToGridMode();
    } else {
        PRINT(2, fprintf(stderr, "\nlocation1: %f,%f", location.x, location.y));
        PRINT(2, fprintf(stderr, "\nspeed: %d", physics->GetSpeed()));
        direction = entryPath.GetDirection(location);
        SetLocation(entryPath.GetMoveLocation(location, physics->GetSpeed() * GetFrameTime()));

#if MODE > 1
        entryPath.ShowPath();
        fprintf(stderr, "\nend direction: %f,%f", direction.x, direction.y);
        fprintf(stderr, "\nlocation2: %f,%f", location.x, location.y);
#endif
    }
}

void Enemy::SetEntryPath(Logic::Path path) { entryPath = path; }

void Enemy::ReturnToGridMode() {
    float dir_angle = GetMoveAngleSmooth(GetGridLocationX(), GetGridLocationY());

    float distance =
        std::pow(location.y - GetGridLocationY(), 2) + std::pow(location.x - GetGridLocationX(), 2);
    PRINT(2, fprintf(stderr, "\nd to grid: %f", distance));

    if (distance < std::pow(physics->GetSpeed() * 2 * GetFrameTime(), 2)) {
        mode = Logic::EnemyMode::INGRID;
        LocateInGrid();
    } else {
        direction = Vector2Normalize(Vector2{std::cos(dir_angle), std::sin(dir_angle)});
        PRINT(2, fprintf(stderr, "direction: %f,%f", direction.x, direction.y));
        MoveAmount(direction);
    }
}

float Enemy::GetGridLocationX() { return gridLocation.x + offset.x; }
float Enemy::GetGridLocationY() { return gridLocation.y + offset.y; }

void Enemy::Spawn() { this->mode = Logic::EnemyMode::ENTRY; };

void Enemy::SetSpawnTime(float time) { this->spawnTime = time; };

void Enemy::NotSpawnedMode() {
    if (spawnTime < GetTime()) {
        mode = Logic::EnemyMode::ENTRY;
        // mode = Logic::Mode::INGRID;
        EntryMode();
    }
}

Vector2 Enemy::GetCorner(int index) {
    assert(index >= 0);
    assert(index < 4);

    switch (index) {
    case 0:
        return Vector2{hitbox.x, hitbox.y};
        break;
    case 1:
        return Vector2{hitbox.x + ENEMYWIDTH, hitbox.y};
        break;
    case 2:
        return Vector2{hitbox.x + ENEMYWIDTH, hitbox.y + ENEMYHEIGHT};
        break;
    case 3:
        return Vector2{hitbox.x, hitbox.y + ENEMYHEIGHT};
        break;
    default:
        return Vector2{0, 0};
    }
}

void Enemy::InitAttackPath() {
    std::vector<Vector2> vec;

    vec.push_back(Vector2{200, 200});
    attackPath.SetPath(vec);
}

void Enemy::AttackMode() {
    // TODO
    PRINT(2, fprintf(stderr, "\nattacking - speed: %d", physics->GetSpeed()));
    attackPath.UpdatePoint(location, direction, physics->GetSpeed() * GetFrameTime());

    if (attackPath.IsComplete()) {
        PRINT(2, fprintf(stderr, "\nend of attack"));
        mode = Logic::RETURNTOGRID;
        ReturnToGridMode();
    } else {
        PRINT(2, fprintf(stderr, "\ncontinue"));
        Vector2 point = attackPath.GetPoint();
        float dir_angle = GetMoveAngleSmooth(point.x, point.y);
        direction = Vector2Normalize(Vector2{std::cos(dir_angle), std::sin(dir_angle)});
        MoveAmount(direction);
        PRINT(2, fprintf(stderr, "\ndirection: %f,%f", direction.x, direction.y));
        PRINT(2, fprintf(stderr, "\ntarget x: %f - y: %f", point.x, point.y));
        PRINT(2, fprintf(stderr, "\nend x: %f - y: %f", location.x, location.y));
    }

#if MODE > 1
    attackPath.ShowPath();
#endif
}

void Enemy::MakeAttack() {
    if (!moving) {
        PRINT(2, fprintf(stderr, "\nMake Attack"));
        mode = Logic::EnemyMode::ATTACK;
        attackPath.Reset();
        moving = true;
        hasDropedBomb = false;
    }
}

float Enemy::GetMoveAngleSmooth(float x, float y) {
    float dir_angle = std::atan2(direction.y, direction.x);
    PRINT(2, fprintf(stderr, "\ndir_angleS %f", dir_angle));
    float target_angel = std::atan2(y - location.y, x - location.x);

    float dif_angle = target_angel - dir_angle;
    PRINT(2,
          fprintf(stderr, "\n\ndir: %f, target: %f, dif: %f", dir_angle, target_angel, dif_angle));

    Color color;
    if (dif_angle > 3.14159) {
        color = BLUE;
        // left
        dif_angle = -6.283 + dif_angle;
        assert(dif_angle <= 0);
        assert(dif_angle > -3.1415);
    } else if (dif_angle < -3.14159) {
        color = RED;
        // right
        dif_angle = 6.283 + dif_angle;
        assert(dif_angle >= 0);
        assert(dif_angle <= 3.1415);
    } else if (dif_angle < 0) {
        color = LIGHTGRAY;
        // left
        assert(dif_angle <= 0);
        assert(dif_angle > -3.1415);
    } else { // dif_angle > 0
        color = PINK;
        assert(dif_angle >= 0);
        assert(dif_angle < 3.1415);
        // right
    }

#if MODE > 1
    DrawCircle(location.x, location.y, 20, color);
#endif

    if (dif_angle < (-1 * physics->GetTurnSpeed())) {
        dif_angle = -physics->GetTurnSpeed();
        color = GREEN;
    } else if (dif_angle > physics->GetTurnSpeed()) {
        dif_angle = physics->GetTurnSpeed();
        color = BLUE;
    }

    dir_angle += dif_angle;

#if MODE > 1
    fprintf(stderr, "\ndir: %f, target: %f, dif: %f", dir_angle, target_angel, dif_angle);
    DrawCircle(location.x, location.y, 10, color);
    DrawLine(location.x, location.y, location.x + std::cos(target_angel) * 20,
             location.y + std::sin(target_angel) * 20, ORANGE);
    DrawLine(location.x, location.y, location.x + std::cos(dir_angle) * 40,
             location.y + std::sin(dir_angle) * 40, BLUE);

#endif
    return dir_angle;
}

void Enemy::SetInGrid() {
    mode = Logic::EnemyMode::INGRID;
    LocateInGrid();
}

void Enemy::SetGameSize(int width, int height) {
    gameWidth = width;
    gameHeight = height;

    UpdateAttackPath();
}

void Enemy::ImageUpdate() {
    if (imageIndex == 1) {
        imageIndex = 0;
    } else {
        imageIndex = 1;
    }
}
