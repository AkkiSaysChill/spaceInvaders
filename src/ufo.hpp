#pragma once
#include <raylib.h>

class UFO {
public:
  UFO();
  ~UFO();
  void Update();
  void Draw();
  void Spawn();
  Rectangle getRect();
  bool alive;

private:
  Vector2 position;
  Texture2D image;
  int spd;
};
