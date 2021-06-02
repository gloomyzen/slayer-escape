#include "playerBase.h"
#include "databasesModule/charactersDatabase.h"
#include "databasesModule/databaseManager.h"
#include "common/coreModule/nodes/widgets/spineNode.h"

using namespace mb::battleModule;

playerBase::playerBase() {}

playerBase::~playerBase() = default;

playerBase* playerBase::initWithId(int id) {
    using namespace databasesModule;
    auto characterDb =
        GET_DATABASE_MANAGER().getDatabase<charactersDatabase>(databaseManager::eDatabaseList::CHARACTER_DB);
    auto data = characterDb->getCharacterById(id);
    auto player = new playerBase();
    player->setName("unit");
    player->loadJson(data->propertyPath);
    player->loadComponent(player, player->getName());
    if (data->hasCollision) {
        auto physics = cocos2d::PhysicsBody::createBox(
            cocos2d::Size(player->getContentSize().width, player->getContentSize().height));
        physics->setDynamic(true);
        player->addComponent(physics);
        physics->setGravityEnable(false);
        physics->setRotationEnable(false);
//        physics->setVelocity(cocos2d::Vec2(50.f, 200.f));
    }
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
