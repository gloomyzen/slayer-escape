#include "playerController.h"
#include "common/debugModule/logManager.h"

using namespace mb::battleModule;

playerController::playerController() {
    setName("playerController");
    loadProperty("battle/" + this->getName(), this);
    initController();
}

void playerController::initController() {
    bigCircle = new stickButton(stickButton::eStickType::BIG_STICK);
    addChild(bigCircle);
    smallCircle = new stickButton(stickButton::eStickType::SMALL_STICK);
    addChild(smallCircle);
    auto scene = cocos2d::Director::getInstance()->getRunningScene();
    if (auto windowNode = scene->findNode("windowViewer")) {
        auto order = windowNode->getLocalZOrder();
        scene->addChild(this, order - 1);
    } else {
        LOG_ERROR("playerController::initController: Can't find windowViewer node");
        return;
    }
}

playerController::~playerController() {}

void playerController::setPawn(playerBase* pBase) {
    player = pBase;
}

void playerController::enableControl() {
    controlAvailable = true;
    // todo action for show controls
}

void playerController::disableControl() {
    controlAvailable = false;
    // todo action for hide controls
}
