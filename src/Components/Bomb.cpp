#include "Bomb.h"
#include "raylib.h"
#include <cassert>
using namespace Components;

Bomb::Bomb(Vector2 loc) { hitbox = Rectangle{loc.x - 4, loc.y, 5, 8}; }
void Bomb::Update() { hitbox.y += GetFrameTime() * BOMBSPEED; }

void Bomb::Draw() {
    DrawRectangle(hitbox.x, hitbox.y, 5, 4, BLUE);
    DrawRectangle(hitbox.x, hitbox.y + 4, 5, 4, RED);
#if MODE > 1
    DrawRectangleRec(hitbox, WHITE);
#endif
}

Vector2 Bomb::GetCorner(int index) {
    assert(index >= 0);
    assert(index < 4);

    switch (index) {
    case 0:
        return Vector2{hitbox.x, hitbox.y};
        break;
    case 1:
        return Vector2{hitbox.x + hitbox.width, hitbox.y};
        break;
    case 2:
        return Vector2{hitbox.x + hitbox.width, hitbox.y + hitbox.height};
        break;
    case 3:
        return Vector2{hitbox.x, hitbox.y + hitbox.height};
        break;
    default:
        return Vector2{0, 0};
    }
}
