#include "battleScene.h"
#include "battleModule/players/playerBase.h"
#include "battleModule/players/stickButton.h"
#include "battleModule/players/playerControllerHelper.h"
#include "common/coreModule/gameManager.h"
#include "common/coreModule/scenes/mainScene.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"
#include "ui/CocosGUI.h"

#ifdef DEBUG
#include "ImGuiEXT/imgui/imgui.h"
#include "ImGuiEXT/imgui/imgui_internal.h"
#include "debugModule/heroProfileDebug.h"
#include "debugModule/soundLibraryDebug.h"
#endif

using namespace mb::battleModule;
using namespace cocos2d;

battleScene::battleScene() {
    this->setName("battleScene");
    loadProperty("scenes/" + this->getName(), dynamic_cast<Node*>(this));
    GET_GAME_MANAGER().getMainScene()->getPhysicsWorld()->setGravity(cocos2d::Vec2(1.f, 1.f));
    initHelpers();
}

battleScene::~battleScene() {
    if (onMoveId && plrController && plrController->getJoystick())
        plrController->getJoystick()->getEmitter()->onMove.disconnect(onMoveId);
    if (onStopId && plrController && plrController->getJoystick())
        plrController->getJoystick()->getEmitter()->onStop.disconnect(onStopId);
}

std::deque<nodeTasks> battleScene::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        world = dynamic_cast<cocos2d::Layer*>(findNode("world"));
        objects = dynamic_cast<cocos2d::Layer*>(findNode("objects"));

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        maze = new battleField();
        maze->setWorldLayer(world);
        maze->setObjectsLayer(objects);
        maze->initLayer(40001);// todo remove after testing

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        plrController = new playerController();
        //todo change it after testings
        player = playerBase::initWithId(20001);
        // todo remove after testing
        {
            // todo нужно поменять структуру уровня, чтобы земля и коллиции находились на разных планах
            //  а коллизиции и объекты были совмещенны
            objects->addChild(player);
        }
        /*
        plrController->disableControl();
        plrController->enableControl();
         */
        onMoveId = plrController->getJoystick()->getEmitter()->onMove.connect([this](float x, float y) {
            if (!plrController || !plrController->getJoystick() || !player) {
                LOG_INFO("battleScene::onMove: player controller is not loaded.");
                return;
            }
            auto dir = getPlayerStateByStick(x, y, plrController->getJoystick()->getStickDistance());
//            if (dir.first.second == ePlayerMoveYDirection::DOWN) LOG_INFO("down");
//            if (dir.first.second == ePlayerMoveYDirection::UP) LOG_INFO("up");
//            if (dir.first.first == ePlayerMoveXDirection::RIGHT) LOG_INFO("right");
//            if (dir.first.first == ePlayerMoveXDirection::LEFT) LOG_INFO("left");
//            if (dir.second == ePlayerMoveIntensive::PLAYER_WALK) LOG_INFO("walk");
//            if (dir.second == ePlayerMoveIntensive::PLAYER_STOP) LOG_INFO("stop");
//            if (dir.second == ePlayerMoveIntensive::PLAYER_RUN) LOG_INFO("run");
            player->movePlayer(dir);
        });

        onStopId = plrController->getJoystick()->getEmitter()->onStop.connect([this]() {
            if (!plrController || !plrController->getJoystick() || !player) {
                LOG_INFO("battleScene::onMove: player controller is not loaded.");
                return;
            }
            player->stopPlayer();
        });

        return eTasksStatus::STATUS_OK;
    });

    return result;
}

void battleScene::initHelpers() {
#ifdef DEBUG
    if (auto imguiLayer = GET_GAME_MANAGER().getMainScene()->getImGuiLayer()) {

        imguiLayer->resetDebugModules();
        imguiLayer->addDebugModules({ "Profile: Heroes", []() {
                                         debugProfile::heroProfileDebug::getInstance().update();
                                     } });
        imguiLayer->addDebugModules({ "Sound library", []() {
                                         debugProfile::soundLibraryDebug::getInstance().update();
                                     } });
#if CC_USE_PHYSICS
        auto clb = [this]() {
            auto temp = physicsDebugDraw;
            auto label = STRING_FORMAT("Physics debug: %s", physicsDebugDraw ? "ON" : "OFF");
            if (ImGui::Button(label.c_str())) {
                physicsDebugDraw = !physicsDebugDraw;
            }
            if (temp != physicsDebugDraw) {
                if (physicsDebugDraw)
                    LOG_INFO("Enable physics debug for current scene.");
                else
                    LOG_INFO("Disable physics debug for current scene.");
                GET_GAME_MANAGER().getMainScene()->getPhysicsWorld()->setDebugDrawMask(
                    physicsDebugDraw ? cocos2d::PhysicsWorld::DEBUGDRAW_ALL : cocos2d::PhysicsWorld::DEBUGDRAW_NONE);
            }
        };
        imguiLayer->addDebugModules({ "Physics debug: OFF", [clb]() {
                                         clb();
                                     } });
#endif
    }
#endif
}
