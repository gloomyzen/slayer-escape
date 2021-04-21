#include "battleScene.h"
#include "battleModule/interface/battleIncomeWidget.h"
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
        // todo check and update theme for battlefield
        battleFieldNode = new battleField();
        battleFieldNode->loadLocation("forest");
        world->addChild(battleFieldNode);

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

    result.emplace_back([this]() {
        // init players
        player.first = new playerData();
        player.first->setPlayerMode(ePlayerMode::PVE);
        player.first->setPlayerPosition(ePlayerPosition::LEFT);
        player.first->setPlayerFraction(ePlayerFraction::HUMAN);
        player.first->setRealUser(true);
        player.first->setBattleField(battleFieldNode);
        player.first->init();


        player.second = new playerData();
        player.second->setPlayerMode(ePlayerMode::PVE);
        player.second->setPlayerPosition(ePlayerPosition::RIGHT);
        player.second->setPlayerFraction(ePlayerFraction::ORC);
        player.second->setRealUser(false);
        player.second->setBattleField(battleFieldNode);
        player.second->init();

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        // ui
        auto goldWidget = dynamic_cast<battleIncomeWidget*>(findNode("incomeGoldWidget"));
        goldWidget->setIcon(battleIncomeWidget::eIconLabelTypes::GOLD);
        goldWidget->setData(gold);

        auto trophiesWidget = dynamic_cast<battleIncomeWidget*>(findNode("incomeTrophiesWidget"));
        trophiesWidget->setIcon(battleIncomeWidget::eIconLabelTypes::TROPHIES);
        trophiesWidget->setData(trophies);

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
            for (auto& item : player.first->getPlayerBuilds()) {
                item.second.slot->setOnTouchEnded([this, &item](){
                       onBuildClick(item.second);
                });
            }

           return eTasksStatus::STATUS_OK;
    });

    return result;
}

void battleScene::onBuildClick(sPlayerBuild& build) {
    //todo wip нужно делать сцену для выбора героев в колоду игрока, чтобы можно было корректно тестить постройки
    LOG_ERROR(STRING_FORMAT("yep %d", build.level));
}
