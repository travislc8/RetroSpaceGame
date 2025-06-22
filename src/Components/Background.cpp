#include "Background.h"
#include "raylib.h"

namespace Components {
Background::Background(float screenWidth, float screenHeight) {
    for (int i = 0; i < STARCOUNT; i++) {
        stars1[i] =
            Vector2{(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)};
    }
    for (int i = 0; i < STARCOUNT; i++) {
        stars2[i] =
            Vector2{(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)};
    }
    lastRedraw = GetTime();
}

void Background::Draw() {
    if ((GetTime() - lastRedraw) > 0.5f) {
        state++;
        lastRedraw = GetTime();
    }
    if (state % 2 == 0) {
        for (int i = 0; i < STARCOUNT; i++) {
            DrawPixelV(stars1[i], WHITE);
        }
    } else {
        for (int i = 0; i < STARCOUNT; i++) {
            DrawPixelV(stars2[i], WHITE);
        }
    }
}

} // namespace Components
