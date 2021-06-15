#ifndef SLAYER_ESCAPE_BATTLEFIELD_H
#define SLAYER_ESCAPE_BATTLEFIELD_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include <vector>

namespace mb::databasesModule {
    struct sMapData;
}
namespace mb::battleModule {
    class battleField {
    public:
        battleField();
        ~battleField();

        void setWorldLayer(cocos2d::Layer* layer) {
            world = layer;
        }
        void setObjectsLayer(cocos2d::Layer* layer) {
            objects = layer;
        }
        cocos2d::Vec2 getPlayerSpawnPosition();
        cocos2d::Vec2 getEnemySpawnPosition();

        void initLayer(int);

    private:
        void insertWalls(databasesModule::sMapData*);
        cocos2d::Layer* world = nullptr;// not owner
        cocos2d::Layer* objects = nullptr;// not owner
        std::vector<cocos2d::Vec2> spawnPlayerPositions;
        std::vector<cocos2d::Vec2> spawnEnemyPositions;
        cocos2d::FastTMXTiledMap* tiledMap = nullptr; //owner
    };
}// namespace mb::battleModule


#endif// SLAYER_ESCAPE_BATTLEFIELD_H
