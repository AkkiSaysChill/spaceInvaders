#pragma once
#include <raylib.h>

class Alien {
public:
  Alien(int type, Vector2 position);
  void Update(int dir);
  void Draw();
  int GetType();
  Rectangle getRect();
  static void UnloadImages();
  static Texture2D alienImage[3];
  int type;
  Vector2 position;

private:
};
