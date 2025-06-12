#include "Fly.h"
#include "../Debug.h"
#include "cassert"
#include <cmath>

namespace Components {

Fly::Fly(Levels::LocationInGrid grid, Vector2 offset) : Enemy(grid, offset) {}

void Fly::LoadTexture() {
    Image img = LoadImage("../src/assets/Fly.png");
    ImageResize(&img, ENEMYWIDTH, ENEMYHEIGHT);
    images[0] = LoadTextureFromImage(img);
    UnloadImage(img);

    Image img2 = LoadImage("../src/assets/Fly2.png");
    ImageResize(&img2, ENEMYWIDTH, ENEMYHEIGHT);
    images[1] = LoadTextureFromImage(img2);
    UnloadImage(img2);
    assert(images[0].id != 0);
    assert(images[1].id != 0);

    src = Rectangle{0, 0, (float)images[0].width, (float)images[0].height};
    dest = Rectangle{0, 0, (float)images[0].width, (float)images[0].height};
    origin = Vector2{(float)images[0].width / 2.0f, (float)images[0].height / 2.0f};
}

void Fly::Draw() {
    if (mode != Logic::NOTSPAWNED) {
#if MODE > 1
        DrawRectangleRec(hitbox, RED);
#endif
        if (GetTime() - imageTime > .5f) {
            if (imageIndex == 1) {
                imageIndex = 0;
            } else {
                imageIndex = 1;
            }
            imageTime = GetTime();
        }

        dest.x = location.x;
        dest.y = location.y;
        assert(dest.x == location.x);
        assert(dest.y == location.y);
        dest.x += (float)images[0].width / 2.0f;
        dest.y += (float)images[0].height / 2.0f;

        float rotation = std::atan2(direction.y, direction.x);
        rotation = rotation * (180 / 3.14159) + 90;
        if (rotation < 0) {
            rotation = 360 + rotation;
        }
        fprintf(stderr, "\nDrawing");
        if (images[imageIndex].id == 0) {
            DrawRectangleRec(hitbox, ORANGE);
        } else {
            PRINT(0, fprintf(stderr, "\nSrc: %f, dest: %f, origin: %f, rotation: %f", src.x, dest.x,
                             origin.x, rotation));
            DrawTexturePro(images[imageIndex], src, dest, origin, rotation, WHITE);
            // DrawTexture(images[imageIndex], location.x, location.y, WHITE);
        }
    }
}

void Fly::UpdateAttackPath() {
    std::vector<Vector2> vec;
    float entryX = (float)GetRandomValue(0, gameWidth);
    vec.push_back(Vector2{entryX, gameHeight / 2.5f});
    vec.push_back(Vector2{entryX - 25, gameHeight / 2.0f});
    vec.push_back(Vector2{entryX + 0, gameHeight - 50.0f});
    vec.push_back(Vector2{entryX + 50, gameHeight - 100.0f});
    vec.push_back(Vector2{entryX + 0, gameHeight - 150.0f});
    vec.push_back(Vector2{entryX - 50, gameHeight - 100.0f});
    vec.push_back(Vector2{entryX + 0, gameHeight - 50.0f});
    vec.push_back(Vector2{entryX + 300, gameHeight / 2.0f});

    attackPath.SetPath(vec);
}

} // namespace Components
