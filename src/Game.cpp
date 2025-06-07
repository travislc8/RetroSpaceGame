#include "Game.h"
#include "Components/Bullet.h"
#include "Components/Bullets.h"
#include "Components/Enemy.h"
#include "Levels/TestLevel.h"
#include "Scoreboard.h"
#include "raylib.h"
#include <cstdlib>
#include <list>

Game::Game() {
    gameWidth = GetScreenWidth() - SCOREBOARDSIZE;
    gameHeight = GetScreenHeight();
    plane = new Components::Plane(gameWidth, gameHeight);
    background = new Components::Background(gameWidth, gameHeight);
    scoreboard =
        new Scoreboard(Vector2{gameWidth, 0}, (float)SCOREBOARDSIZE, (float)GetScreenHeight());
    level = new Levels::TestLevel(gameWidth, gameHeight);
}

Game::~Game() {
    delete plane;
    delete background;
    delete scoreboard;
    delete level;
}

void Game::Update() {
    KeyInput();
    bullets.Update();
    level->Update();
    CheckBullets();
    CheckBombs();
    CheckCollisions();
}

void Game::Draw() {
    background->Draw();
    bullets.Draw();
    plane->Draw();
    level->Draw();
    scoreboard->Draw();
}

void Game::KeyInput() {
    if (IsKeyPressed(KEY_SPACE)) {
        if (scoreboard->GetLives() > 0)
            bullets.Add(plane->GetLocation());
    }
    if (IsKeyPressed(KEY_R)) {
        if (scoreboard->GetLives() > 0)
            plane->Reset();
    }

    if (IsKeyDown(KEY_RIGHT)) {
        plane->Move(GetFrameTime() * MOVESPEED);
    } else if (IsKeyDown(KEY_LEFT)) {
        plane->Move(GetFrameTime() * MOVESPEED * -1);
    }
}

void Game::CheckBullets() {
    std::list<Components::Bullet*> bulletList = bullets.GetBullets();
    std::list<Components::Enemy*> enemyList = level->GetEnemyList();
    for (auto bullet : bulletList) {
        for (auto enemy : enemyList) {
            if (CheckCollisionRecs(bullet->hitbox, enemy->hitbox)) {
                bullets.Remove(bullet);
                level->Remove(enemy);
                scoreboard->Add(500);
            }
        }
    }
};

void Game::CheckBombs() {}

void Game::CheckCollisions() {
    std::list<Components::Enemy*> enemyList = level->GetEnemyList();
    bool collision;
    if (!plane->ShouldDestroy()) {
        for (auto enemy : enemyList) {
            collision = false;
            if (CheckCollisionPointTriangle(enemy->GetCorner(0), plane->GetPoint(0),
                                            plane->GetPoint(1), plane->GetPoint(2))) {
                collision = true;
            } else if (CheckCollisionPointTriangle(enemy->GetCorner(1), plane->GetPoint(0),
                                                   plane->GetPoint(1), plane->GetPoint(2))) {
                collision = true;
            } else if (CheckCollisionPointTriangle(enemy->GetCorner(2), plane->GetPoint(0),
                                                   plane->GetPoint(1), plane->GetPoint(2))) {
                collision = true;
            } else if (CheckCollisionPointTriangle(enemy->GetCorner(3), plane->GetPoint(0),
                                                   plane->GetPoint(1), plane->GetPoint(2))) {
                collision = true;
            }

            if (collision) {
                scoreboard->RemoveLife();
                enemy->SetDestroy();
                plane->SetDestroy();
                if (scoreboard->GetLives() < 0) {
                    exit(4);
                }
            }
        }
    }
}
