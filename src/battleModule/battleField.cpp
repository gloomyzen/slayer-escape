#include "battleField.h"
#include "battleModule/mapTile.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"
#include "databasesModule/databaseManager.h"
#include "databasesModule/mapsDatabase.h"
#include "databasesModule/tilesDatabase.h"
#include <tuple>

using namespace mb::battleModule;

battleField::battleField() {}

battleField::~battleField() {}

void battleField::initLayer(int id) {
    using namespace databasesModule;
    // generate a maze
    auto mapsDb = GET_DATABASE_MANAGER().getDatabase<mapsDatabase>(databaseManager::eDatabaseList::MAPS_DB);
    auto tilesDb = GET_DATABASE_MANAGER().getDatabase<tilesDatabase>(databaseManager::eDatabaseList::TILES_DB);
    auto map = mapsDb->getMapById(id);
    if (map == nullptr) {
        LOG_ERROR(STRING_FORMAT("battleField::initLayer: Can't find map bu id - %d", id));
        return;
    }
    auto mapSize = cocos2d::Size();
    for (const auto& row : map->map) {
        for (const auto& col : row.second) {
            if (auto tile = tilesDb->getTileById(col.second)) {
                auto node = new mapTile();
                node->initWithProp(STRING_FORMAT("tile_%d", tile->id), tile->nodePath);
                node->setPositionX(node->getContentSize().width * node->getScale() * row.first);
                node->setPositionY(node->getContentSize().height * node->getScale() * col.first);
                if (mapSize.width < node->getContentSize().width * node->getScale() * (row.first + 1)) {
                    mapSize.width = node->getContentSize().width * node->getScale() * (row.first + 1);
                }
                if (mapSize.height < node->getContentSize().height * node->getScale() * (col.first + 1)) {
                    mapSize.height = node->getContentSize().height * node->getScale() * (col.first + 1);
                }
                if (tile->type == databasesModule::eTileTypes::WALL || tile->type == databasesModule::eTileTypes::WALL_DESTROY) {
                    auto physics = cocos2d::PhysicsBody::createBox(
                        cocos2d::Size(node->getContentSize().width, node->getContentSize().height), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
                    physics->setCategoryBitmask(0x03);
                    physics->setCollisionBitmask(0x03);
                    physics->setGravityEnable(false);
                    physics->setDynamic(false);
                    physics->setRotationEnable(false);
                    physics->setMass(100.f);
                    physics->setMoment(0.f);
                    node->addComponent(physics);
                }
                if (tile->type == databasesModule::eTileTypes::WALL || tile->type == databasesModule::eTileTypes::WALL_DESTROY) {
                    objects->addChild(node);
                } else {
                    world->addChild(node);
                }
            }
        }
    }
    world->setContentSize(mapSize);
    objects->setContentSize(mapSize);
}
