#include "Enemy.h"
#include "raylib.h"

Enemy::Enemy() {
    location = Vector2{50, 50};
    hitbox = Rectangle{50, 50, 50, 50};
}

Enemy::~Enemy() {}

void Enemy::Draw() { DrawRectangleRec(hitbox, RED); }

void Enemy::SetLocation(Vector2 location) { this->location = location; }
