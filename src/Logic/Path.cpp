#include "Path.h"
#include "raylib.h"
#include "raymath.h"
#include <cassert>
#include <cmath>
#include <iterator>
#include <stdio.h>

namespace Logic {
Path::Path() {}

Path::Path(std::vector<Vector2> points) {
    for (auto point : points) {
        this->points.push_back(Vector2{point.x, point.y});
    }
    // fprintf(stderr, "\nPath init vector size: %d, [0].x = %f", (int)points.size(), points[0].x);
    assert(points.size() > 0);
}

void Path::UpdatePoint(Vector2 loc, Vector2 direction, float speed) {
    UpdateTargetIndex(loc, direction, speed);
}

Vector2 Path::GetPoint() {
    assert(pointIndex >= 0);
    assert(pointIndex < points.size());
    if (pointIndex >= 0 && pointIndex < points.size()) {
        return Vector2{points[pointIndex].x, points[pointIndex].y};
    }
    return Vector2{0, 0};
}

void Path::UpdateTargetIndex(Vector2 loc, Vector2 direction, float speed) {
    // fprintf(stderr, "\ndirection.x: %f, direction.y: %f", direction.x, direction.y);
    // fprintf(stderr, "\npoints count %d", (int)points.size());
    bool change = false;

    float distance =
        std::pow(loc.y - points[pointIndex].y, 2) + std::pow(loc.x - points[pointIndex].x, 2);
    fprintf(stderr, "\nGetting Target - distance: %f, speed %f", distance, speed);
    if (distance < speed * 2) {
        fprintf(stderr, "\nnext");
        change = true;
        pointIndex++;
    }
    /*
    if (!change) {
        if (direction.y < 0.0f) {
            if (loc.y <= points[current].y) {
                next++;
                change = true;
            } else {
                fprintf(stderr, "\nno change");
                fprintf(stderr, "\nloc.y: %f points[].y: %f", loc.y, points[current].y);
            }

        } else {
            if (loc.y >= points[current].y) {
                next++;
                change = true;
            } else {
                fprintf(stderr, "\nno change");
                fprintf(stderr, "\nloc.y: %f points[].y: %f", loc.y, points[current].y);
            }
        }
    }
    */

    fprintf(stderr, "\nPre point index: %d ", pointIndex);
    if (pointIndex >= points.size()) {
        fprintf(stderr, "\nCompleted\n\n");
        pointIndex = -1;
    }
    fprintf(stderr, "\nPost point index: %d ", pointIndex);
    assert(pointIndex < (int)points.size());
}

Vector2 Path::GetDirection(Vector2 loc) {
    return Vector2Normalize(Vector2{points[pointIndex].x - loc.x, points[pointIndex].y - loc.y});
}

void Path::ShowPath() {
    for (int i = 0; i < points.size() - 1; i++) {
        DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, WHITE);
    }
}

Vector2 Path::GetMoveLocation(Vector2 currentLoc, int distance) {
    Vector2 result = currentLoc;
    // fprintf(stderr, "\nstart distance: %d", distance);
    while (distance > 0) {
        // fprintf(stderr, "\npoint %d - %f,%f", pointIndex, points[pointIndex].x,
        // points[pointIndex].y);
        float distance_squared = std::pow((points[pointIndex].x - currentLoc.x), 2) +
                                 std::pow((points[pointIndex].y - currentLoc.y), 2);
        float distance_to_point = std::sqrt(distance_squared);
        if (distance > distance_to_point && pointIndex < points.size() - 1) {
            distance -= distance_to_point;
            currentLoc = points[pointIndex];
            pointIndex++;
            // fprintf(stderr, "\noverlap - distance: %d", distance);

        } else {
            if (pointIndex == points.size()) {
                pointIndex = -1;
            } else {
                // fprintf(stderr, "\nGetting Point");
                Vector2 direction = Vector2Normalize(Vector2{points[pointIndex].x - currentLoc.x,
                                                             points[pointIndex].y - currentLoc.y});
                // fprintf(stderr, "\ndirection2: %f,%f", direction.x, direction.y);
                result.x = currentLoc.x + (direction.x * distance);
                result.y = currentLoc.y + (direction.y * distance);
                // fprintf(stderr, "\nresult: %f,%f", result.x, result.y);
                distance = 0;
                // pointIndex = GetTargetPoint(result, direction, pointIndex, distance);
            }
        }
    }
    return result;
}

bool Path::IsComplete() {
    if (pointIndex >= points.size())
        return true;
    else
        return false;
}

void Path::Reset() { pointIndex = 0; }

} // namespace Logic
