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
    // pointIndex = entryPath->GetTargetPoint(location, direction, pointIndex);
    if (pointIndex == -1) {
        state = 2;
        MoveState2();
    } else {
        fprintf(stderr, "\nlocation1: %f,%f", location.x, location.y);
        direction = entryPath->GetDirection(location, pointIndex);
        SetLocation(entryPath->GetMoveLocation(location, pointIndex, ENEMYSPEED));
        fprintf(stderr, "\nend direction: %f,%f", direction.x, direction.y);
        fprintf(stderr, "\nlocation2: %f,%f", location.x, location.y);
        entryPath->ShowPath();
    }
    /*
if (pointIndex == -1) {
    state = 2;
    MoveState2();
} else {
    direction = Vector2Normalize(Vector2{entryPath->GetPoint(pointIndex).x - location.x,
                                         entryPath->GetPoint(pointIndex).y - location.y});
    MoveAmount(direction);
}
    */
}

void Enemy::SetEntryPath(Logic::Path* path) { entryPath = path; }

void Enemy::MoveState2() {
    float dir_angle = std::atan2(direction.y, direction.x);
    float target_angel =
        std::atan2(GetGridLocationY() - location.y, GetGridLocationX() - location.x);
    // fprintf(stderr, "\ntarget: %f, direction: %f", target_angel, dir_angle);

    float dif_angle = target_angel - dir_angle;
#if MODE == 1
    DrawLine(location.x, location.y, location.x + std::cos(target_angel) * 20,
             location.y + std::sin(target_angel) * 20, ORANGE);
    DrawLine(location.x, location.y, location.x + std::cos(dir_angle) * 20,
             location.y + std::sin(dir_angle) * 20, BLUE);

#endif
    fprintf(stderr, "\ndir: %f, target: %f, dif: %f", dir_angle, target_angel, dif_angle);
    if (std::abs(dif_angle) > TURNSPEED) {
        dif_angle = TURNSPEED;
        fprintf(stderr, "\ncap");
    }
    dir_angle += dif_angle;
    fprintf(stderr, "new dir: %f", dir_angle);

    float distance =
        std::pow(location.y - GetGridLocationY(), 2) + std::pow(location.x - GetGridLocationX(), 2);
    fprintf(stderr, "\nd to grid: %f", distance);
    if (distance < std::pow(ENEMYSPEED * GetFrameTime(), 2)) {
        state = 1;
        LocateInGrid();
    } else {
        direction = Vector2Normalize(Vector2{std::cos(dir_angle), std::sin(dir_angle)});
        // fprintf(stderr, "\nlocation: %f,%f", location.x, location.y);
        // fprintf(stderr, "\ntarget: %f,%f", gridLocation.x, gridLocation.y);
        // fprintf(stderr, "\ndirection: %f,%f", direction.x, direction.y);
        MoveAmount(direction);
    }
}

float Enemy::GetGridLocationX() { return gridLocation.x + offset.x; }
float Enemy::GetGridLocationY() { return gridLocation.y + offset.y; }
