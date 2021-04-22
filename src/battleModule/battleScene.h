#ifndef MERCENARY_BATTLES_BATTLESCENE_H
#define MERCENARY_BATTLES_BATTLESCENE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/scenes/windows/windowBase.h"
#include "battleField.h"
#include <tuple>

namespace mb::battleModule {

    class battleScene
        : public common::coreModule::nodeProperties
        , public cocos2d::Layer
        , public taskHolder {
      public:
        battleScene();
        ~battleScene();
        std::deque<nodeTasks> getTasks() override;

      private:
        // world section
        cocos2d::Layer* world = nullptr; //owner
        battleField* maze = nullptr; //owner
        bool physicsDebugDraw = false;
    };
}// namespace mb::battleModule


#endif// MERCENARY_BATTLES_BATTLESCENE_H
