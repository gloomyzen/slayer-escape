#include "battleField.h"
#include "common/debugModule/logManager.h"
#include "databasesModule/databaseManager.h"
#include "databasesModule/mapsDatabase.h"
#include "databasesModule/tilesDatabase.h"
#include <map>
#include <tuple>

using namespace mb::battleModule;

battleField::battleField() {
    this->setName("battleField");
//    loadProperty("scenes/" + this->getName(), dynamic_cast<Node*>(this));
}

battleField::~battleField() {}

void battleField::initLayer(int id) {
    using namespace databasesModule;
    //generate a maze
    auto mapsDb = GET_DATABASE_MANAGER().getDatabase<mapsDatabase>(databaseManager::eDatabaseList::MAPS_DB);
    auto map = mapsDb->getMapById(id);
    if (map == nullptr) {
        //todo log error
        return;
    }
    std::vector<int> ground;
    std::vector<int> wall;
    auto tilesDb = GET_DATABASE_MANAGER().getDatabase<tilesDatabase>(databaseManager::eDatabaseList::TILES_DB);
    for (const auto& tileId : map->fill) {
        tilesDb->getTileById(tileId);
    }
    std::map<int, std::map<int, cocos2d::Node*>> result;
    for (int x = 0; x < map->width; ++x) {
        for (int y = 0; y < map->height; ++y) {
            result[x][y] = new cocos2d::Node();
        }
    }
}
