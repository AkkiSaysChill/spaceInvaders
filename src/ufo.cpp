#include "ufo.hpp"
#include <raylib.h>

UFO::UFO() {
  image = LoadTexture("assets/alien_ship.png");
  alive = false;
}

UFO::~UFO() { UnloadTexture(image); }

void UFO::Spawn() {
  position.y = 90;
  int side = GetRandomValue(0, 1);

  if (side == 0) {
    position.x = 25;
    spd = 3;
  } else {
    position.x = GetScreenWidth() - image.width - 25;
    spd = -3;
  }

  alive = true;
}

void UFO::Update() {
  if (alive) {
    position.x += spd;
    if (position.x > GetScreenWidth() - image.width - 25) {
      alive = false;
    }
    if (position.x < 25) {
      alive = false;
    }
  }
}

void UFO::Draw() {
  if (alive) {
    DrawTextureV(image, position, WHITE);
  }
}

Rectangle UFO::getRect() {
  if (alive) {
    return {position.x, position.y, float(image.width), float(image.height)};
  } else {
    return {position.x, position.y, 0, 0};
  }
}
