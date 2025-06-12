#include "Bullet.h"
using namespace Components;

Bullet::Bullet(Vector2 loc) { hitbox = Rectangle{loc.x - 4, loc.y, 5, 8}; }
void Bullet::Update() { hitbox.y -= GetFrameTime() * BULLETSPEED; }

void Bullet::Draw() {
    DrawRectangle(hitbox.x, hitbox.y, 5, 4, RED);
    DrawRectangle(hitbox.x, hitbox.y + 4, 5, 4, BLUE);
#if MODE > 1
    DrawRectangleRec(hitbox, WHITE);
#endif
}
