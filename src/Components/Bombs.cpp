#include "Bombs.h"
#include "Bomb.h"
#include "raylib.h"

using namespace Components;

Bombs::Bombs() { lastShot = 0; }
Bombs::~Bombs() {
    for (auto bullet : bombs) {
        delete bullet;
    }
    bombs.clear();
}

void Bombs::Update() {
    for (auto it = bombs.begin(); it != bombs.end();) {
        if ((*it)->hitbox.y > maxY) {
            delete *it;
            it = bombs.erase(it);
        } else if ((*it)->ShouldDestroy()) {
            delete *it;
            it = bombs.erase(it);
        } else {
            (*it)->Update();
            it++;
        }
    }
}

void Bombs::Draw() {
    for (auto bullet : bombs) {
        bullet->Draw();
    }
}

void Bombs::Add(Vector2 vec) {
    if (bombs.size() < 2)
        bombs.push_back(new Bomb(vec));
}

std::list<Bomb*> Bombs::GetBombs() { return bombs; }

void Bombs::Remove(Bomb* rbullet) {
    for (auto lbullet : bombs) {
        if (rbullet == lbullet) {
            lbullet->SetDestroy();
            break;
        }
    }
}
