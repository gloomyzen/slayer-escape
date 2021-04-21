#include "playerData.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"

using namespace mb::battleModule;
using namespace common::coreModule;

playerData::playerData() {}
playerData::~playerData() {}

void playerData::init() {
    if (inited || !bf)
        return;
    inited = true;
    initCastle();
    initBuilds();
}

void playerData::initCastle() {
    // init castle
    castle = new battleObject();
    castle->setObjectSize(battleObject::eBattleObjectSize::LARGE);
    bf->getBaseNode()->addChild(castle);
    auto pos = bf->getBaseData().castlePos;
    if (playerPosition == ePlayerPosition::RIGHT) {
        auto bfSize = bf->getBaseNode()->getContentSize();
        pos.x += castle->getContentSize().width;
        pos.x = bfSize.width - pos.x;
    }
    castle->setPosition(pos);
    auto sprite = new nodeWithProperties<cocos2d::Sprite>();
    sprite->setName("build");
    auto fraction = fractionNames.find(getPlayerFraction());
    if (fraction != fractionNames.end()) {
        sprite->loadJson(STRING_FORMAT("battle/buildings/%sCastle", fraction->second.c_str()));
        sprite->loadComponent(sprite, "build");
    } else {
        LOG_ERROR("playerData::initCastle: can't find fraction for load sprite");
        return;
    }
    if (playerPosition == ePlayerPosition::RIGHT) {
        sprite->setFlippedX(true);
    }
    castle->getHolder()->addChild(sprite);
}

void playerData::initBuilds() {
    auto positions = bf->getBaseData().buildingPos;
    if (playerPosition == ePlayerPosition::RIGHT) {
        //todo remove after test
        return;
        std::reverse(positions.begin(), positions.end());
    }

    for (size_t i = 0; i < positions.size(); ++i) {
        sPlayerBuild playerBuild;
        playerBuild.level = i + 1;
        playerBuild.slot = new buildSlot();
        playerBuild.pos = positions[i];
        playerBuild.slot->setPosition(positions[i]);
        bf->getBaseNode()->addChild(playerBuild.slot);
        playerBuilds.insert({ playerBuild.level, playerBuild });
    }
}
