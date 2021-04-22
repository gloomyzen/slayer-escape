#include "battleField.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"
#include "databasesModule/databaseManager.h"
#include "databasesModule/mapsDatabase.h"
#include "databasesModule/tilesDatabase.h"
#include "battleModule/mapTile.h"
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
    // generate a maze
    auto mapsDb = GET_DATABASE_MANAGER().getDatabase<mapsDatabase>(databaseManager::eDatabaseList::MAPS_DB);
    auto tilesDb = GET_DATABASE_MANAGER().getDatabase<tilesDatabase>(databaseManager::eDatabaseList::TILES_DB);
    auto map = mapsDb->getMapById(id);
    if (map == nullptr) {
        // todo log error
        return;
    }
    for (const auto& row : map->map) {
        for (const auto& col : row.second) {
            if (auto tile = tilesDb->getTileById(col.second)) {
                auto node = new mapTile();
                node->initWithProp(STRING_FORMAT("tile_%d", tile->id), tile->nodePath);

            }
        }
    }
}
