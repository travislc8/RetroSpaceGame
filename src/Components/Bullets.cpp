#include "Bullets.h"
#include "raylib.h"

using namespace Components;

Bullets::Bullets() { lastShot = 0; }
Bullets::~Bullets() {
    for (auto bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

void Bullets::Update() {
    for (auto it = bullets.begin(); it != bullets.end();) {
        if ((*it)->hitbox.y < 0) {
            delete *it;
            it = bullets.erase(it);
        } else if ((*it)->ShouldDestroy()) {
            delete *it;
            it = bullets.erase(it);
        } else {
            (*it)->Update();
            it++;
        }
    }
}

void Bullets::Draw() {
    for (auto bullet : bullets) {
        bullet->Draw();
    }
}

void Bullets::Add(Vector2 vec) { bullets.push_back(new Bullet(vec)); }

std::list<Bullet*> Bullets::GetBullets() { return bullets; }

void Bullets::Remove(Bullet* rbullet) {
    for (auto lbullet : bullets) {
        if (rbullet == lbullet) {
            lbullet->SetDestroy();
            break;
        }
    }
}
