
#include "load_asset.hpp"

AssetLoader::AssetLoader(const std::string &filename) {
  pakFile.open(filename, std::ios::binary);
  if (!pakFile) {
    std::cerr << "Failed to open asset pack!\n";
    return;
  }

  // Read the index
  AssetEntry entry;
  while (pakFile.read(reinterpret_cast<char *>(&entry), sizeof(AssetEntry))) {
    assets.push_back(entry);
  }
}

std::vector<unsigned char> AssetLoader::LoadAsset(const std::string &name) {
  for (const auto &asset : assets) {
    if (name == asset.filename) {
      std::vector<unsigned char> buffer(asset.size);
      pakFile.seekg(asset.offset);
      pakFile.read(reinterpret_cast<char *>(buffer.data()), asset.size);
      return buffer;
    }
  }
  std::cerr << "Asset not found: " << name << "\n";
  return {};
}
