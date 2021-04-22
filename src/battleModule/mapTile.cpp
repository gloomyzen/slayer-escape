#include "mapTile.h"

using namespace mb::battleModule;

mapTile::mapTile() {}

mapTile::~mapTile() {}

void mapTile::initWithProp(const std::string& name, const std::string& path) {
    this->setName(name);
    loadProperty(path, dynamic_cast<cocos2d::Sprite*>(this));
    init();
}
