#include "battleField.h"
#include "battleModule/mapTile.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"
#include "databasesModule/databaseManager.h"
#include "databasesModule/mapsDatabase.h"
#include "databasesModule/tilesDatabase.h"
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
                switch (tile->type) {

                case UNDEFINED:
                case GROUND:
                    world->addChild(node);
                    break;
                case WALL:
                case WALL_DESTROY:
                    objects->addChild(node);
                    break;
                case SPAWN_PLAYER: {
                    world->addChild(node);
                    spawnPlayerPositions.emplace_back(node->getPosition().x + node->getContentSize().width / 2, node->getPosition().y + node->getContentSize().height / 2);
                } break;
                case SPAWN_ENEMY: {
                    world->addChild(node);
                    spawnEnemyPositions.emplace_back(node->getPosition().x + node->getContentSize().width / 2, node->getPosition().y + node->getContentSize().height / 2);
                } break;
                }
            }
        }
    }
    world->setContentSize(mapSize);
    objects->setContentSize(mapSize);
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
