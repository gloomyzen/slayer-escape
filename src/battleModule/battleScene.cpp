#include "battleScene.h"
#include "ui/CocosGUI.h"
#include "common/debugModule/logManager.h"
#include "common/coreModule/gameManager.h"
#include "common/coreModule/scenes/mainScene.h"
#include "common/utilityModule/stringUtility.h"

#ifdef DEBUG
#include "debugModule/heroProfileDebug.h"
#include "debugModule/soundLibraryDebug.h"
#endif

using namespace mb::battleModule;
using namespace cocos2d;

battleScene::battleScene() {
    this->setName("battleScene");
    loadProperty("scenes/" + this->getName(), dynamic_cast<Node*>(this));

#ifdef DEBUG
    if (GET_GAME_MANAGER().getMainScene()->getImGuiLayer()) {
        GET_GAME_MANAGER().getMainScene()->getImGuiLayer()->resetDebugModules();
        GET_GAME_MANAGER().getMainScene()->getImGuiLayer()->addDebugModules([](){
               debugProfile::heroProfileDebug::getInstance().update();
               debugProfile::soundLibraryDebug::getInstance().update();
        });
    }
#endif
}

battleScene::~battleScene() {}

std::deque<nodeTasks> battleScene::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        world = dynamic_cast<cocos2d::Layer*>(findNode("world"));
        // todo load and add level here

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        auto scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));
        if (!scrollView) {
            return eTasksStatus::STATUS_ERROR_BREAK;
        }
        auto worldSize = world->getContentSize();
        scrollView->setInnerContainerSize(cocos2d::Size(worldSize.width * 0.8f, worldSize.height * 0.8f));
        world->setMarkDirty();

        return eTasksStatus::STATUS_OK;
    });

    return result;
}
