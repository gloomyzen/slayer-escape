#include "mapTile.h"

using namespace mb::battleModule;

mapTile::mapTile() = default;

mapTile::~mapTile() = default;

void mapTile::initWithProp(const std::string& name, const std::string& path) {
    this->setName("tile");
    loadJson(path);
    loadComponent(this, "tile");
    this->setName(name);
}
