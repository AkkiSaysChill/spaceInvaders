#include "game.hpp"
#include "alien.hpp"
#include "obsticle.hpp"
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <vector>

Game::Game() {
  music = LoadMusicStream("assets/audios/music.mp3");
  PlayMusicStream(music);
  explosion = LoadSound("assets/audios/explosion.wav");
  alienExp = LoadSound("assets/audios/alien_exp.wav");
  ouch = LoadSound("assets/audios/hitHurt.wav");
  GameOverSound = LoadSound("assets/audios/go.mp3");
  InitGame();
}

Game::~Game() {
  Alien::UnloadImages();
  UnloadMusicStream(music);
}

void Game::Update() {

  if (run) {

    double currentTime = GetTime();
    if (currentTime - lastUfo > ufoTime) {
      ufo.Spawn();
      lastUfo = GetTime();
      ufoTime = GetRandomValue(10, 20);
    }

    for (auto &laser : spaceship.lasers) {
      laser.Update();
    }
    MoveAlien();
    AlienShoot();

    for (auto &laser : alienLaser) {
      laser.Update();
    }
    ufo.Update();
    CheckCollisions();

    DeleteLaser();
  } else {
    if (IsKeyDown(KEY_ENTER)) {
      Reset();
      InitGame();
    }
  }
}
void Game::Draw() {
  spaceship.Draw();
  ufo.Draw();

  for (auto &laser : spaceship.lasers) {
    laser.Draw();
  }

  for (auto &obsticle : obsticle) {
    obsticle.Draw();
  }

  for (auto &Alien : aliens) {
    Alien.Draw();
  }

  for (auto &laser : alienLaser) {
    laser.Draw();
  }
}
void Game::HandleInput() {
  if (run) {

    if (IsKeyDown(KEY_A)) {
      spaceship.MoveLeft();
    } else if (IsKeyDown(KEY_D)) {
      spaceship.MoveRight();
    } else if (IsKeyDown(KEY_SPACE)) {
      spaceship.FireLaser();
    }
  }
}
void Game::DeleteLaser() {
  for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
    if (!it->active) {
      it = spaceship.lasers.erase(it);

    } else {
      ++it;
    }
  }
  for (auto it = alienLaser.begin(); it != alienLaser.end();) {
    if (!it->active) {
      it = alienLaser.erase(it);

    } else {
      ++it;
    }
  }
}

std::vector<Obsticle> Game::CreateObsticles() {
  // Obsticle tempObsticle({0, 0}); // Temporary object to get grid size
  int obsticleWidth = Obsticle::grid[0].size() * 3;
  float gap = (GetScreenWidth() - (4 * obsticleWidth)) / 5;

  for (int i = 0; i < 4; i++) {
    float offsetX = (i + 1) * gap + i * obsticleWidth;
    obsticle.push_back(Obsticle({offsetX, float(GetScreenHeight() - 200)}));
  }
  return obsticle;
}

std::vector<Alien> Game::CreateALiens() {
  std::vector<Alien> aliens;
  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 11; col++) {

      int alienType;
      if (row == 0) {
        alienType = 1;
      } else if (row == 1 || row == 2) {
        alienType = 2;
      } else {
        alienType = 3;
      }

      float x = 75 + col * 55;
      float y = 110 + row * 55;
      aliens.push_back(Alien(alienType, {x, y}));
    }
  }
  return aliens;
}

void Game::MoveAlien() {
  for (auto &alien : aliens) {
    if (alien.position.x + alien.alienImage[alien.type - 1].width >
        GetScreenWidth() - 25) {
      aliensDir = -1;
      MoveAlienDown(4);
    } else if (alien.position.x < 25) {
      aliensDir = 1;
      MoveAlienDown(4);
    }

    alien.Update(aliensDir);
  }
}

void Game::MoveAlienDown(int distance) {
  for (auto &alien : aliens) {
    alien.position.y += distance;
  }
}

void Game::AlienShoot() {
  double currentTime = GetTime();
  double ShotCooldown = 1.0; // Set a cooldown time (adjust as needed)

  if ((currentTime - LastShot >= ShotCooldown) && !aliens.empty()) {
    int randomIndex = GetRandomValue(0, aliens.size() - 1);
    Alien &alien = aliens[randomIndex];

    alienLaser.push_back(
        Laser({alien.position.x + alien.alienImage[alien.type - 1].width / 2,
               alien.position.y + alien.alienImage[alien.type - 1].height},
              6));

    LastShot = currentTime; // Update last shot time correctly
  }
}

void Game::CheckCollisions() {
  // spaceship laser
  for (auto &laser : spaceship.lasers) {
    auto it = aliens.begin();
    while (it != aliens.end()) {
      if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
        if (it->type == 1) {
          score += 100;
        } else if (it->type == 2) {
          score += 200;
        } else if (it->type == 3) {
          score += 300;
        }
        checkHighScore();
        it = aliens.erase(it); // Erase and get the next valid iterator
        laser.active = false;  // Deactivate the laser
        PlaySound(alienExp);
      } else {
        ++it; // Only increment if no collision happened
      }
    }

    for (auto &obsticle : obsticle) {
      auto it = obsticle.blocks.begin();
      while (it != obsticle.blocks.end()) {
        if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
          it = obsticle.blocks.erase(it);
          laser.active = false;
        } else {
          ++it;
        }
      }
    }

    if (CheckCollisionRecs(ufo.getRect(), laser.getRect())) {
      ufo.alive = false;
      laser.active = false;
      score += 500;
      checkHighScore();
      PlaySound(explosion);
    }
  }

  // Alien laser
  for (auto &laser : alienLaser) {
    if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
      laser.active = false;
      lives--;
      PlaySound(ouch);
      if (lives == 0) {
        GameOver();
      }
    }
    for (auto &obsticle : obsticle) {
      auto it = obsticle.blocks.begin();
      while (it != obsticle.blocks.end()) {
        if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
          it = obsticle.blocks.erase(it);
          laser.active = false;
        } else {
          ++it;
        }
      }
    }
  }

  // alien collision with obsticle
  for (auto &alien : aliens) {
    for (auto &obsticle : obsticle) {
      auto it = obsticle.blocks.begin();
      while (it != obsticle.blocks.end()) {
        if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
          it = obsticle.blocks.erase(it);

        } else {
          it++;
        }
      }
    }
    if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
      GameOver();
    }
  }
}

void Game::GameOver() {

  PlaySound(GameOverSound);
  run = false;
}

void Game::InitGame() {
  obsticle = CreateObsticles();

  aliens = CreateALiens();
  aliensDir = 1;
  lives = 3;
  run = true;
  LastShot = 0;
  lastUfo = 0.0;
  ufoTime = GetRandomValue(10, 20);
  score = 0;
  highScore = loadHighScore();
}

void Game::Reset() {
  spaceship.Reset();
  aliens.clear();
  alienLaser.clear();
  obsticle.clear();
}

void Game::checkHighScore() {
  if (score > highScore) {
    highScore = score;
    saveHighScore(highScore);
  }
}

void Game::saveHighScore(int highScore) {
  std::ofstream highScoreFile("highScore.txt");
  if (highScoreFile.is_open()) {
    highScoreFile << highScore;
    highScoreFile.close();
  } else {
    std::cerr << "Failed to save file" << std::endl;
  }
}

int Game::loadHighScore() {
  int loadedScore = 0;
  std::ifstream highScoreFile("highScore.txt");
  if (highScoreFile.is_open()) {
    highScoreFile >> loadedScore;
    highScoreFile.close();
  } else {
    std::cerr << "Failed to load Score" << std::endl;
  }
  return loadedScore;
}
