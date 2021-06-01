#include "playerBase.h"
#include "databasesModule/charactersDatabase.h"
#include "databasesModule/databaseManager.h"
#include "common/coreModule/nodes/widgets/spineNode.h"

using namespace mb::battleModule;

playerBase::playerBase() {}

playerBase* playerBase::initWithId(int id) {
    using namespace databasesModule;
    auto player = new playerBase();
    auto characterDb =
        GET_DATABASE_MANAGER().getDatabase<charactersDatabase>(databaseManager::eDatabaseList::CHARACTER_DB);
    auto data = characterDb->getCharacterById(id);
    player->setName("unit");
    player->loadJson(data->propertyPath);
    player->loadComponent(player, player->getName());
    if (!data->isSpine) {
        auto sprite = new cocos2d::Sprite();
        sprite->setName("sprite");
        player->loadComponent(sprite, sprite->getName());
        player->addChild(sprite);
    } else {
        auto spine = new common::coreModule::spineNode();
        spine->setName("spine");
        player->loadComponent(spine, spine->getName());
        player->addChild(spine);
    }

    return player;
}

playerBase::~playerBase() = default;
