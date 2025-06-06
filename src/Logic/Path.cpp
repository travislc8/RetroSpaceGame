#include "Path.h"
#include "raylib.h"
#include "raymath.h"
#include <cassert>
#include <cmath>
#include <stdio.h>

namespace Logic {
Path::Path() {}

Path::Path(std::vector<Vector2> points) {
    for (auto point : points) {
        this->points.push_back(Vector2{point.x, point.y});
    }
    fprintf(stderr, "\nPath init vector size: %d, [0].x = %f", (int)points.size(), points[0].x);
    assert(points.size() > 0);
}

Vector2 Path::GetPoint(int index) {
    if (index > points.size() || index < 0) {
        fprintf(stderr, "\nInvalid Index in GetPoint: Index = %d", index);
    } else {
        return Vector2{points[index].x, points[index].y};
    }
    return Vector2{0, 0};
}

int Path::GetTargetPoint(Vector2 loc, Vector2 direction, int current) {
    int next = current;
    // TODO temp
    fprintf(stderr, "\ndirection.x: %f, direction.y: %f", direction.x, direction.y);
    bool change = false;

    if (direction.x < 0.0f) {
        if (loc.x <= points[current].x) {
            next++;
            change = true;
        } else {
            fprintf(stderr, "\nno change");
            fprintf(stderr, "\nloc.x: %f points[].x: %f", loc.x, points[current].x);
        }

    } else {
        if (loc.x >= points[current].x) {
            next++;
            change = true;
        } else {
            fprintf(stderr, "\nno change");
            fprintf(stderr, "\nloc.x: %f points[].x: %f", loc.x, points[current].x);
        }
    }

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

    fprintf(stderr, "\ncurrent = %d - next = %d", current, next);
    if (next >= (int)points.size()) {
        fprintf(stderr, "\nCompleted\n\n");
        next = -1;
    }
    assert(next < (int)points.size());

    return next;
}

Vector2 Path::GetDirection(Vector2 loc, int pointIndex) {
    return Vector2Normalize(Vector2{points[pointIndex].x - loc.x, points[pointIndex].y - loc.y});
}

void Path::ShowPath() {
    for (int i = 0; i < points.size() - 1; i++) {
        DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, WHITE);
    }
}

Vector2 Path::GetMoveLocation(Vector2 currentLoc, int& nextPoint, int distance) {
    Vector2 result = currentLoc;
    fprintf(stderr, "\nstart distance: %d", distance);
    while (distance > 0) {
        fprintf(stderr, "\npoint %d - %f,%f", nextPoint, points[nextPoint].x, points[nextPoint].y);
        float distance_squared = std::pow((points[nextPoint].x - currentLoc.x), 2) +
                                 std::pow((points[nextPoint].y - currentLoc.y), 2);
        float distance_to_point = std::sqrt(distance_squared);
        if (distance > distance_to_point && nextPoint < points.size() - 1) {
            distance -= distance_to_point;
            currentLoc = points[nextPoint];
            nextPoint++;
            fprintf(stderr, "\noverlap - distance: %d", distance);

        } else {
            fprintf(stderr, "\nGetting Point");
            Vector2 direction = Vector2Normalize(
                Vector2{points[nextPoint].x - currentLoc.x, points[nextPoint].y - currentLoc.y});
            fprintf(stderr, "\ndirection2: %f,%f", direction.x, direction.y);
            result.x = currentLoc.x + (direction.x * distance);
            result.y = currentLoc.y + (direction.y * distance);
            fprintf(stderr, "\nresult: %f,%f", result.x, result.y);
            distance = 0;
            nextPoint = GetTargetPoint(result, direction, nextPoint);
        }
    }
    return result;
}

} // namespace Logic
