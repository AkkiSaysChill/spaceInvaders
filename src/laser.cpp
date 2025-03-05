#include "laser.hpp"
#include <iostream>
#include <raylib.h>

Laser::Laser(Vector2 position, int spd) {
  this->position = position;
  this->spd = spd;
  active = true;
}

void Laser::Draw() {
  if (active) {
    DrawRectangle(position.x, position.y, 4, 15, {234, 214, 60, 255});
  }
}

void Laser::Update() {
  position.y += spd;
  if (active) {
    if (position.y > GetScreenHeight() - 100 || position.y < 0) {
      active = false;
    }
  }
}

Rectangle Laser::getRect() {
  Rectangle rect;
  rect.x = position.x;
  rect.y = position.y;
  rect.width = 4;
  rect.height = 15;
  return rect;
}
