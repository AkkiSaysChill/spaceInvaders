#include "spaceship.hpp"
#include "laser.hpp"
#include <raylib.h>

Spaceship::Spaceship() {
  image = LoadTexture("assets/ship.png");

  shoot = LoadSound("assets/audios/laserShoot.wav");
  position.x = (GetScreenWidth() - image.width) / 2;
  position.y = (GetScreenHeight() - (image.height * 1.5) - 100);
  lastFire = 0.0;
}

Spaceship::~Spaceship() { UnloadTexture(image); }

void Spaceship::Draw() {
  float scale = 3.0f; // Scale the large image down.
  float rotation = 0.0f;
  Color tint = WHITE;

  Rectangle sourceRec = {0.0f, 0.0f, (float)image.width, (float)image.height};
  Vector2 origin = {(float)image.width / 2, (float)image.height / 2};
  Rectangle destRec = {position.x, position.y, (float)image.width * scale,
                       (float)image.height * scale};

  DrawTexturePro(image, sourceRec, destRec, origin, rotation, tint);
}

void Spaceship::MoveLeft() {
  position.x -= 7;
  if (position.x < 35) {
    position.x = 35;
  }
}

void Spaceship::MoveRight() {
  position.x += 7;
  if (position.x > GetScreenWidth() - image.width - 75) {
    position.x = GetScreenWidth() - image.width - 75;
  }
}

void Spaceship::FireLaser() {
  if (GetTime() - lastFire >= 0.35) {

    PlaySound(shoot);
    lasers.push_back(
        Laser({position.x + image.width / 2 + 13, position.y}, -6));
    lastFire = GetTime();
  }
}

Rectangle Spaceship::getRect() {
  float scale = 3.0f; // Match the scale used in Draw()
  return {position.x, position.y, image.width * scale, image.height * scale};
}

void Spaceship::Reset() {
  position.x = (GetScreenWidth() - (image.width * 3.0)) / 2.0;
  position.y = GetScreenHeight() - (image.height * 1.5) - 100;
  lasers.clear();
}
