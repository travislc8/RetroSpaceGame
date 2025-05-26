#include "Plane.h"
#include "raylib.h"
#include <iostream>

Plane::Plane(int screen_width, int screen_height) {
    Image img = LoadImage("../src/assets/plane.png");
    plane = LoadTextureFromImage(img);
    UnloadImage(img);

    if (plane.id == 0) {
        exit(2);
    }
    planeWidth = 60;
    planeHeight = 50;
    maxX = screen_width - (planeWidth / 2);
    minX = 0 + planeWidth / 2;
    points = new Vector2[3];
    points[0] = Vector2{800, 700};
    points[1] = Vector2{points[0].x - (planeWidth / 2.0f), points[0].y + planeHeight};
    points[2] = Vector2{points[0].x + (planeWidth / 2.0f), points[0].y + planeHeight};
}

Plane::~Plane() {
    UnloadTexture(plane);
    delete points;
}

void Plane::Move(int distance) {
    int x = points[0].x + (float)distance;
    if (x > maxX) {
        points[0].x = maxX;
        points[1].x = maxX - (planeWidth / 2.0f);
        points[2].x = maxX + (planeWidth / 2.0f);
    } else if (x < minX) {
        points[0].x = minX;
        points[1].x = minX - (planeWidth / 2.0f);
        points[2].x = minX + (planeWidth / 2.0f);
    } else {
        points[0].x = x;
        points[1].x = x - (planeWidth / 2.0f);
        points[2].x = x + (planeWidth / 2.0f);
    }
}

void Plane::Move(Vector2 vec) {
    if (vec.x > maxX) {
        points[0].x = maxX;
        points[1].x = maxX - (planeWidth / 2.0f);
        points[2].x = maxX + (planeWidth / 2.0f);
    } else if (vec.x < minX) {
        points[0].x = minX;
        points[1].x = minX - (planeWidth / 2.0f);
        points[2].x = minX + (planeWidth / 2.0f);
    } else {
        points[0].x = vec.x;
        points[1].x = vec.x - (planeWidth / 2.0f);
        points[2].x = vec.x + (planeWidth / 2.0f);
    }
}

void Plane::Draw() {
    if (plane.id == 0) {
        exit(3);
    }
    DrawTexture(plane, points[0].x - (planeWidth / 2.0f) - 1, points[0].y, WHITE);
    DrawTriangle(points[0], points[1], points[2], BLUE);
}

Vector2 Plane::GetLocation() { return points[0]; }
