#include "battleField.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"
#include "databasesModule/databaseManager.h"
#include "databasesModule/mapsDatabase.h"
#include <random>
#include <algorithm>
#include <iterator>

using namespace mb::battleModule;

battleField::battleField() {}

battleField::~battleField() {}

void battleField::initLayer(int id) {
    using namespace databasesModule;
    // generate a maze
    auto mapsDb = GET_DATABASE_MANAGER().getDatabase<mapsDatabase>(databaseManager::eDatabaseList::MAPS_DB);
    auto map = mapsDb->getMapById(id);
    if (map == nullptr) {
        LOG_ERROR(STRING_FORMAT("battleField::initLayer: Can't find map bu id - %d", id));
        return;
    }
//    world->setContentSize(mapSize);
//    objects->setContentSize(mapSize);
}

cocos2d::Vec2 battleField::getPlayerSpawnPosition() {
    if (!spawnPlayerPositions.empty()) {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(spawnPlayerPositions.begin(), spawnPlayerPositions.end(), g);
        auto pos = spawnPlayerPositions.front();
        spawnPlayerPositions.erase(spawnPlayerPositions.begin());
        return pos;
    }

    LOG_ERROR(STRING_FORMAT("battleField::getPlayerSpawnPosition: Can't find next spawn positions"));
    return cocos2d::Vec2(155.f, 175.f);
}

cocos2d::Vec2 battleField::getEnemySpawnPosition() {
    if (!spawnEnemyPositions.empty()) {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(spawnEnemyPositions.begin(), spawnEnemyPositions.end(), g);
        auto pos = spawnEnemyPositions.front();
        spawnEnemyPositions.erase(spawnEnemyPositions.begin());
        return pos;
    }

    LOG_ERROR(STRING_FORMAT("battleField::getEnemySpawnPosition: Can't find next spawn positions"));
    return cocos2d::Vec2(155.f, 175.f);
}
