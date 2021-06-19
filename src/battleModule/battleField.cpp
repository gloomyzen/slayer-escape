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

battleField::~battleField() {
    spawnPlayerPositions.clear();
    spawnEnemyPositions.clear();
    delete tiledMap;
    tiledMap = nullptr;
    tileObjMap.clear();
}

void battleField::initLayer(int id) {
    using namespace databasesModule;
    // generate a maze
    auto mapsDb = GET_DATABASE_MANAGER().getDatabase<mapsDatabase>(databaseManager::eDatabaseList::MAPS_DB);
    auto map = mapsDb->getMapById(id);
    if (map == nullptr) {
        LOG_ERROR(STRING_FORMAT("battleField::initLayer: Can't find map by id - %d", id));
        return;
    }
    tiledMap = cocos2d::FastTMXTiledMap::create(map->mapPath);
    world->addChild(tiledMap);
    collectObjectData();
    //insert collisions walls
    insertWalls(map);

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

void battleField::insertWalls(databasesModule::sMapData* map) {
    auto layer = tiledMap->getLayer("bg");
    if (layer) {
        const auto& size = layer->getLayerSize();
        for (auto x = 0; x < static_cast<int>(size.width); ++x) {
            for (auto y = 0; y < static_cast<int>(size.height); ++y) {
                auto propGid = layer->getTileGIDAt({static_cast<float>(x), static_cast<float>(y)});
                auto prop = tiledMap->getPropertiesForGID(propGid);
                if (prop.getType() != cocos2d::Value::Type::NONE) {
                    auto test2 = "";
                }

//                auto tile = layer->getTileAt({static_cast<float>(x), static_cast<float>(y)});

//                if (tile) {
//                    tile->
//                }
            }
        }
    }
    return;
    auto walls = tiledMap->getObjectGroup(map->wallProperty);
    if (walls) {
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
                block->setName(
                    STRING_FORMAT("%s_%s", objectName.empty() ? "block" : objectName.c_str(), objectId.c_str()));
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
    }
}
void battleField::collectObjectData() {
    tileObjMap.clear();
    if (!tiledMap) return;
    auto data = tiledMap->getObjectGroups();
    for (const auto& item : data) {
        sBattleFieldPiece piece;
        for (const auto& obj : item->getObjects()) {
            if (obj.getType() == cocos2d::Value::Type::MAP) {
                auto values = obj.asValueMap();
                for (const auto& value : values) {
                    if (value.first == "height" && value.second.getType() == cocos2d::Value::Type::FLOAT) {
                        piece.size.height = value.second.asFloat();
                    } else if (value.first == "width" && value.second.getType() == cocos2d::Value::Type::FLOAT) {
                        piece.size.width = value.second.asFloat();
                    } else if (value.first == "x" && value.second.getType() == cocos2d::Value::Type::FLOAT) {
                        piece.vec.x = value.second.asFloat();
                    } else if (value.first == "y" && value.second.getType() == cocos2d::Value::Type::FLOAT) {
                        piece.vec.y = value.second.asFloat();
                    } else if (value.first == "gid" && value.second.getType() == cocos2d::Value::Type::STRING) {
                        piece.gid = std::stoi(value.second.asString());
                    }
                }
            }
        }
        if (piece.gid != -1) {
            auto prop = tiledMap->getPropertiesForGID(piece.gid);
            if (prop.getType() != cocos2d::Value::Type::NONE) {
                // todo get prop
            }
            tileObjMap.insert({ piece.gid, piece });
        }
    }
}
