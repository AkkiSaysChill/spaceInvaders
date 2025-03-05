#include "alien.hpp"
#include <raylib.h>

Texture2D Alien::alienImage[3] = {};

Alien::Alien(int type, Vector2 position) {
  this->type = type;
  this->position = position;

  if (alienImage[type - 1].id == 0) {
  }

  switch (type) {
  case 1:
    alienImage[0] = LoadTexture("assets/alien_3.png");
    break;
  case 2:
    alienImage[1] = LoadTexture("assets/alien_2.png");
    break;
  case 3:
    alienImage[2] = LoadTexture("assets/alien_1.png");
  }
}

void Alien::Draw() { DrawTextureV(alienImage[type - 1], position, WHITE); }

int Alien::GetType() { return type; }

void Alien::UnloadImages() {
  for (int i = 0; i < 4; i++) {
    UnloadTexture(alienImage[i]);
  }
}

void Alien::Update(int dir) { position.x += dir; }

Rectangle Alien::getRect() {
  return {position.x, position.y, float(alienImage[type - 1].width),
          float(alienImage[type - 1].height)};
}
