#include "Bullets.h"
#include "raylib.h"
#include <iostream>

Bullets::Bullets() { lastShot = 0; }
Bullets::~Bullets() {
    for (auto bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

Bullets::Bullet::Bullet(Vector2 loc) { rect = Rectangle{loc.x, loc.y, 8, 10}; }

void Bullets::Update() {
    for (auto it = bullets.begin(); it != bullets.end();) {
        if ((*it)->rect.y < 0) {
            delete *it;
            it = bullets.erase(it);
        } else {
            (*it)->Update();
            it++;
        }
    }
}

void Bullets::Bullet::Update() { rect.y -= 12; }

void Bullets::Draw() {
    for (auto bullet : bullets) {
        DrawRectangle(bullet->rect.x - 4, bullet->rect.y, 5, 4, RED);
        DrawRectangle(bullet->rect.x - 4, bullet->rect.y + 2, 5, 4, BLUE);
    }
}

void Bullets::Add(Vector2 vec) { bullets.push_back(new Bullet(vec)); }
