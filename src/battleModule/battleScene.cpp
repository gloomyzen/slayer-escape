#include "battleScene.h"
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
    GET_GAME_MANAGER().getMainScene()->initWithPhysics();
    GET_GAME_MANAGER().getMainScene()->getPhysicsWorld()->setGravity(cocos2d::Vec2(1.f, 1.f));
#ifdef DEBUG
    if (GET_GAME_MANAGER().getMainScene()->getImGuiLayer()) {
#if CC_USE_PHYSICS
        auto clb = [this]() {
            auto temp = physicsDebugDraw;
            if (ImGui::Button("Debug physics")) {
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
#else
        auto clb = []() {};
#endif
        GET_GAME_MANAGER().getMainScene()->getImGuiLayer()->resetDebugModules();
        GET_GAME_MANAGER().getMainScene()->getImGuiLayer()->addDebugModules([clb]() {
            debugProfile::heroProfileDebug::getInstance().update();
            debugProfile::soundLibraryDebug::getInstance().update();
            clb();
        });
    }
#endif
}

battleScene::~battleScene() {}

std::deque<nodeTasks> battleScene::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        world = dynamic_cast<cocos2d::Layer*>(findNode("world"));
        maze = new battleField();
        maze->setLayer(world);
        maze->initLayer(40001);// todo remove after testing

        return eTasksStatus::STATUS_OK;
    });

    return result;
}
