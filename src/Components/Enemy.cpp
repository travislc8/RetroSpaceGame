#include "Enemy.h"
#include "../Logic/Path.h"
#include "raylib.h"
#include "raymath.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>

using namespace Components;

Enemy::Enemy(Levels::LocationInGrid gridLocation, Vector2 offset) {
    this->offset = offset;
    this->gridLocation = gridLocation;
    LocateInGrid();
    hitbox = Rectangle{location.x, location.y, ENEMYWIDTH, ENEMYHEIGHT};
    state = 0;
    direction = Vector2Normalize(Vector2{1, 1});
    moving = true;
}

Enemy::~Enemy() {}

void Enemy::Draw() { DrawRectangleRec(hitbox, RED); }

void Enemy::SetLocation(Vector2 location) { MoveTo(location); }

void Enemy::Update() {
    // 0 - entry path
    // 1 - move with grid
    // 2 - go to grid
    if (state == 0) {
        MoveState0();
    } else if (state == 1) {
        LocateInGrid();
    } else if (state == 2) {
        MoveState2();
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
}

void Enemy::MoveAmount(Vector2 vec) {
    location.x += vec.x * ENEMYSPEED * GetFrameTime();
    location.y += vec.y * ENEMYSPEED * GetFrameTime();
    hitbox.x = location.x;
    hitbox.y = location.y;
    fprintf(stderr, "\nnew x: %f", location.x);
}

void Enemy::MoveTo(Vector2 vec) {
    this->location.x = vec.x;
    this->location.y = vec.y;
    hitbox.x = location.x;
    hitbox.y = location.y;
}

void Enemy::MoveState0() {
    if (pointIndex == -1) {
        state = 2;
        MoveState2();
    } else {
        fprintf(stderr, "\nlocation1: %f,%f", location.x, location.y);
        direction = entryPath->GetDirection(location, pointIndex);
        SetLocation(entryPath->GetMoveLocation(location, pointIndex, ENEMYSPEED * GetFrameTime()));
        fprintf(stderr, "\nend direction: %f,%f", direction.x, direction.y);
        fprintf(stderr, "\nlocation2: %f,%f", location.x, location.y);
#if MODE == 1
        entryPath->ShowPath();
#endif
    }
}

void Enemy::SetEntryPath(Logic::Path* path) { entryPath = path; }

void Enemy::MoveState2() {
    float dir_angle = std::atan2(direction.y, direction.x);
    fprintf(stderr, "\ndir_angleS %f", dir_angle);
    float target_angel =
        std::atan2(GetGridLocationY() - location.y, GetGridLocationX() - location.x);

    float dif_angle = target_angel - dir_angle;
    fprintf(stderr, "\n\ndir: %f, target: %f, dif: %f", dir_angle, target_angel, dif_angle);

    Color color;
    if (dif_angle > 3.14159) {
        color = BLUE;
        // left
        dif_angle = -6.283 + dif_angle;
        fprintf(stderr, "\nCheck1");
        assert(dif_angle <= 0);
        assert(dif_angle > -3.1415);
    } else if (dif_angle < -3.14159) {
        color = RED;
        // right
        dif_angle = 6.283 + dif_angle;
        fprintf(stderr, "\nCheck2");
        assert(dif_angle >= 0);
        assert(dif_angle <= 3.1415);
    } else if (dif_angle < 0) {
        color = LIGHTGRAY;
        // left
        fprintf(stderr, "\nCheck3");
        assert(dif_angle <= 0);
        assert(dif_angle > -3.1415);
    } else { // dif_angle > 0
        color = PINK;
        assert(dif_angle >= 0);
        assert(dif_angle < 3.1415);
        // right
        fprintf(stderr, "\nCheck4");
    }

#if MODE == 1
    DrawCircle(location.x, location.y, 20, color);
#endif

    if (dif_angle < (-1 * TURNSPEED)) {
        dif_angle = -TURNSPEED;
        fprintf(stderr, "\ncap");
        color = GREEN;
    } else if (dif_angle > TURNSPEED) {
        dif_angle = TURNSPEED;
        fprintf(stderr, "\ncap");
        color = BLUE;
    }

    dir_angle += dif_angle;
    fprintf(stderr, "\ndir: %f, target: %f, dif: %f", dir_angle, target_angel, dif_angle);

#if MODE == 1
    DrawCircle(location.x, location.y, 10, color);
    DrawLine(location.x, location.y, location.x + std::cos(target_angel) * 20,
             location.y + std::sin(target_angel) * 20, ORANGE);
    DrawLine(location.x, location.y, location.x + std::cos(dir_angle) * 40,
             location.y + std::sin(dir_angle) * 40, BLUE);

#endif

    float distance =
        std::pow(location.y - GetGridLocationY(), 2) + std::pow(location.x - GetGridLocationX(), 2);
    fprintf(stderr, "\nd to grid: %f", distance);

    if (distance < std::pow(ENEMYSPEED * 2 * GetFrameTime(), 2)) {
        state = 1;
        LocateInGrid();
    } else {
        direction = Vector2Normalize(Vector2{std::cos(dir_angle), std::sin(dir_angle)});
        fprintf(stderr, "direction: %f,%f", direction.x, direction.y);
        MoveAmount(direction);
    }
}

float Enemy::GetGridLocationX() { return gridLocation.x + offset.x; }
float Enemy::GetGridLocationY() { return gridLocation.y + offset.y; }
