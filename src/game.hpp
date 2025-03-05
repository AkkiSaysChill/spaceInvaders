#pragma once
#include "alien.hpp"
#include "obsticle.hpp"
#include "spaceship.hpp"
#include "ufo.hpp"
#include <raylib.h>
#include <vector>

class Game {
public:
  Game();
  ~Game();
  void Draw();
  void Update();
  void HandleInput();
  bool run;
  int GetLives() const { return lives; }
  int score;
  Music music;
  int highScore;

private:
  void DeleteLaser();
  std::vector<Obsticle> CreateObsticles();
  std::vector<Alien> CreateALiens();
  Spaceship spaceship;
  std::vector<Obsticle> obsticle;
  std::vector<Alien> aliens;
  void MoveAlien();
  void MoveAlienDown(int distance);
  int aliensDir;
  void AlienShoot();
  std::vector<Laser> alienLaser;
  void CheckCollisions();
  constexpr static float alienInterval = 0.35;
  float LastShot;
  int lives;
  void LoadAsset();
  void GameOver();
  UFO ufo;
  void Reset();
  void InitGame();
  float ufoTime;
  float lastUfo;
  void checkHighScore();
  int loadHighScore();
  void saveHighScore(int highScore);
  Sound explosion;
};
