#include "battle3dScene.h"
//#include "battleModule/players/playerBase.h"
//#include "battleModule/players/stickButton.h"
//#include "battleModule/players/playerControllerHelper.h"
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

using namespace mb::battle3dModule;
using namespace cocos2d;

battle3dScene::battle3dScene() {
    this->setName("battle3dScene");
    loadProperty("scenes/" + this->getName(), dynamic_cast<Node*>(this));
    GET_GAME_MANAGER().getMainScene()->getPhysicsWorld()->setGravity(cocos2d::Vec2(1.f, 1.f));
    initHelpers();
}

battle3dScene::~battle3dScene() {
//    if (onMoveId && plrController && plrController->getJoystick())
//        plrController->getJoystick()->getEmitter()->onMove.disconnect(onMoveId);
//    if (onStopId && plrController && plrController->getJoystick())
//        plrController->getJoystick()->getEmitter()->onStop.disconnect(onStopId);
}

std::deque<nodeTasks> battle3dScene::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        world = dynamic_cast<cocos2d::Layer*>(findNode("world"));
        objects = dynamic_cast<cocos2d::Layer*>(findNode("objects"));
        auto map = cocos2d::FastTMXTiledMap::create("images/battle/maps/firstMap.tmx");
        world->addChild(map);
        auto walls = map->getObjectGroup("walls");

        for (auto item : walls->getObjects()) {
            auto type = item.getType();
            if (type == cocos2d::Value::Type::MAP) {
                auto values = item.asValueMap();
                for (auto test : values) {
                    auto temp = test.second.getType();
                    auto name = test.first;
                    auto testset = "";
                }
                auto tesm = "";
            }
            auto tesmp = ";";

        }

        Size CC_UNUSED s = map->getContentSize();
        CCLOG("ContentSize: %f, %f", s.width, s.height);

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
//        maze = new battleField();
//        maze->setWorldLayer(world);
//        maze->setObjectsLayer(objects);
//        maze->initLayer(40001);// todo remove after testing

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
//        plrController = new playerController();
//        //todo change it after testings
//        player = playerBase::initWithId(20001);
//        if (maze)
//            player->setPosition(maze->getPlayerSpawnPosition());
//        objects->addChild(player);
//        enemy = playerBase::initWithId(21001);
//        if (maze)
//            enemy->setPosition(maze->getEnemySpawnPosition());
//        objects->addChild(enemy);
        /*
        plrController->disableControl();
        plrController->enableControl();
         */
//        onMoveId = plrController->getJoystick()->getEmitter()->onMove.connect([this](float x, float y) {
//            if (!plrController || !plrController->getJoystick() || !player) {
//                LOG_INFO("battle3dScene::onMove: player controller is not loaded.");
//                return;
//            }
//            auto dir = getPlayerStateByStick(x, y, plrController->getJoystick()->getStickDistance());
//            player->movePlayer(dir);
//        });
//
//        onStopId = plrController->getJoystick()->getEmitter()->onStop.connect([this]() {
//            if (!plrController || !plrController->getJoystick() || !player) {
//                LOG_INFO("battle3dScene::onMove: player controller is not loaded.");
//                return;
//            }
//            player->stopPlayer();
//        });
//        scheduleUpdate();
//        trackLookAt(player);
//        lookAt();

        return eTasksStatus::STATUS_OK;
    });

    return result;
}

void battle3dScene::update(float dt) {
    Node::update(dt);
//    lookAt();
}

void battle3dScene::trackLookAt(cocos2d::Node* node) {
    lookAtNode = node;
}

void battle3dScene::lookAt() {
    if (lookAtNode) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto roomPos = cocos2d::Vec2((visibleSize.width / 2) - lookAtNode->getPositionX(), (visibleSize.height / 2) - lookAtNode->getPositionY());
        if (roomPos.x > 0.f) roomPos.x = 0.f;
        if (roomPos.y > 0.f) roomPos.y = 0.f;
        if (roomPos.x < (world->getContentSize().width - visibleSize.width) * -1) roomPos.x = (world->getContentSize().width - visibleSize.width) * -1;
        if (roomPos.y < (world->getContentSize().height - visibleSize.height) * -1) roomPos.y = (world->getContentSize().height - visibleSize.height) * -1;
        setPosition(roomPos);
    }
}

void battle3dScene::initHelpers() {
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