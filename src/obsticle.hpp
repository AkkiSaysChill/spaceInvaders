#pragma once
#include "block.hpp"
#include <raylib.h>
#include <vector>

class Obsticle {
public:
  Obsticle(Vector2 position);
  void Draw();
  Vector2 position;
  std::vector<Block> blocks;
  static std::vector<std::vector<int>> grid;
};
