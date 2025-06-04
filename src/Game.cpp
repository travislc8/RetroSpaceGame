#include "Game.h"
#include "Components/Bullet.h"
#include "Components/Bullets.h"
#include "Components/Enemy.h"
#include "Levels/TestLevel.h"
#include "raylib.h"
#include <list>

Game::Game() {
    plane = new Components::Plane(GetScreenWidth(), GetScreenHeight());
    level = Levels::TestLevel();
    background = Components::Background();
}

Game::~Game() { delete plane; }

void Game::Update() {
    KeyInput();
    bullets.Update();
    level.Update();
    CheckBullets();
    CheckBombs();
}

void Game::Draw() {
    background.Draw();
    bullets.Draw();
    plane->Draw();
    // level.Update();
    level.Draw();
}

void Game::KeyInput() {
    if (IsKeyPressed(KEY_SPACE)) {
        bullets.Add(plane->GetLocation());
    }

    if (IsKeyDown(KEY_RIGHT)) {
        plane->Move(GetFrameTime() * MOVESPEED);
    } else if (IsKeyDown(KEY_LEFT)) {
        plane->Move(GetFrameTime() * MOVESPEED * -1);
    }
}

void Game::CheckBullets() {
    std::list<Components::Bullet*> bulletList = bullets.GetBullets();
    std::list<Components::Enemy*> enemyList = level.GetEnemyList();
    for (auto bullet : bulletList) {
        for (auto enemy : enemyList) {
            if (CheckCollisionRecs(bullet->hitbox, enemy->hitbox)) {
                bullets.Remove(bullet);
                level.Remove(enemy);
            }
        }
    }
};

void Game::CheckBombs() {}
