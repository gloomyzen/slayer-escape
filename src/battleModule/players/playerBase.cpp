#include "playerBase.h"
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
    player->loadData(data);
    player->setName("unit");
    player->loadJson(data->propertyPath);
    player->loadComponent(player, player->getName());
    if (data->hasCollision) {
        auto physics = cocos2d::PhysicsBody::createBox(
            cocos2d::Size(player->getContentSize().width, player->getContentSize().height));
        physics->setDynamic(true);
        player->addComponent(physics);
        player->setPhysicsComponent(physics);
        physics->setGravityEnable(false);
        physics->setRotationEnable(false);
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

void playerBase::loadData(databasesModule::sCharacterData* data) {
    characterData = data;
    playerDirection = !data->flipX ? ePlayerMoveXDirection::RIGHT : ePlayerMoveXDirection::LEFT;
}

void playerBase::movePlayer(
    std::pair<std::pair<ePlayerMoveXDirection, ePlayerMoveYDirection>, ePlayerMoveIntensive> dir) {
    if (!physicsComponent) return;
    auto move = cocos2d::Vec2::ZERO;
    auto speed = 0.f;
    if (dir.second == ePlayerMoveIntensive::PLAYER_WALK) {
        speed = characterData->stats->speed / 2;
    } else if (dir.second == ePlayerMoveIntensive::PLAYER_RUN) {
        speed = characterData->stats->speed;
    }
    if (dir.first.first == ePlayerMoveXDirection::RIGHT) {
        move.x = speed;
    } else if (dir.first.first == ePlayerMoveXDirection::LEFT) {
        move.x = speed * -1;
    }
    if (dir.first.second == ePlayerMoveYDirection::UP) {
        move.y = speed;
    } else if (dir.first.second == ePlayerMoveYDirection::DOWN) {
        move.y = speed * -1;
    }
    physicsComponent->setVelocity(move);
}

void playerBase::stopPlayer() {
    if (!physicsComponent) return;
    physicsComponent->setVelocity(cocos2d::Vec2::ZERO);
}
