
#ifndef LOAD_ASSETS_HPP
#define LOAD_ASSETS_HPP

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

struct AssetEntry {
  char filename[100];
  uint32_t size;
  uint32_t offset;
};

class AssetLoader {
  std::ifstream pakFile;
  std::vector<AssetEntry> assets;

public:
  AssetLoader(const std::string &filename);
  std::vector<unsigned char> LoadAsset(const std::string &name);
};

#endif // LOAD_ASSETS_HPP
