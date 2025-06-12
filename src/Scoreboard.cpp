#include "Scoreboard.h"
#include "iomanip"
#include "raylib.h"
#include <cassert>
#include <string>

Scoreboard::Scoreboard(Vector2 origin, float width, float height) {
    Image img = LoadImage("../src/assets/plane.png");
    ImageResize(&img, 50, 50);
    planeTexture = LoadTextureFromImage(img);
    UnloadImage(img);
    assert(planeTexture.id != 0);

    this->origin = origin;
    this->width = width;
    this->height = height;
}

void Scoreboard::Draw() {
    DrawRectangle(origin.x, origin.y, width, height, BLACK);
    DrawLine(origin.x, origin.y, origin.x, origin.y + height, WHITE);

    std::string score_string = "Score: ";
    score_string.append(std::to_string(score));
    DrawText(score_string.c_str(), origin.x + 10, origin.y + 200, 20, WHITE);
    for (int i = 0; i < lives - 1; i++) {
        DrawTexture(planeTexture, origin.x + 10 + (i * 60), origin.y + 500, WHITE);
    }
}

void Scoreboard::Add(int value) { score += value; }

void Scoreboard::RemoveLife() { lives -= 1; }
int Scoreboard::GetLives() { return lives; }
void Scoreboard::AddLife() { lives += 1; }
void Scoreboard::SetLives(int lives) { this->lives = lives; }
