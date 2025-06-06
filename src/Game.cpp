#include "Game.h"
#include "Components/Bullet.h"
#include "Components/Bullets.h"
#include "Components/Enemy.h"
#include "Levels/TestLevel.h"
#include "Scoreboard.h"
#include "raylib.h"
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
