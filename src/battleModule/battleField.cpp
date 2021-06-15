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
        LOG_ERROR(STRING_FORMAT("battleField::initLayer: Can't find map by id - %d", id));
        return;
    }
    auto tiled = cocos2d::FastTMXTiledMap::create(map->mapPath);
    world->addChild(tiled);
    auto walls = tiled->getObjectGroup(map->wallsObject);

    //insert collisions walls
    for (const auto& item : walls->getObjects()) {
        auto type = item.getType();
        cocos2d::Size objectSize;
        cocos2d::Vec2 objectPos;
        std::string objectId;
        std::string objectName;
        if (type == cocos2d::Value::Type::MAP) {
            auto values = item.asValueMap();
            for (const auto& value : values) {
                if (value.first == "height" && value.second.getType() == cocos2d::Value::Type::FLOAT) {
                    objectSize.height = value.second.asFloat();
                } else if (value.first == "width" && value.second.getType() == cocos2d::Value::Type::FLOAT) {
                    objectSize.width = value.second.asFloat();
                } else if (value.first == "x" && value.second.getType() == cocos2d::Value::Type::FLOAT) {
                    objectPos.x = value.second.asFloat();
                } else if (value.first == "y" && value.second.getType() == cocos2d::Value::Type::FLOAT) {
                    objectPos.y = value.second.asFloat();
                } else if (value.first == "id" && value.second.getType() == cocos2d::Value::Type::STRING) {
                    objectId = value.second.asString();
                } else if (value.first == "name" && value.second.getType() == cocos2d::Value::Type::STRING) {
                    objectName = value.second.asString();
                }
            }
            auto block = new cocos2d::Node();
            block->setName(STRING_FORMAT("%s_%s", objectName.empty() ? "block" : objectName.c_str(), objectId.c_str()));
            block->setPosition(objectPos);
            block->setContentSize(objectSize);

            auto physics = cocos2d::PhysicsBody::createBox(objectSize, cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
            physics->setCategoryBitmask(0x03);
            physics->setCollisionBitmask(0x03);
            physics->setGravityEnable(false);
            physics->setDynamic(false);
            physics->setRotationEnable(false);
            physics->setMass(100.f);
            physics->setMoment(0.f);
            block->addComponent(physics);

            objects->addChild(block);
        }

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
