#ifndef MERCENARY_BATTLES_BATTLESCENE_H
#define MERCENARY_BATTLES_BATTLESCENE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/scenes/windows/windowBase.h"
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
        cocos2d::Layer* world = nullptr;
    };
}// namespace mb::battleModule


#endif// MERCENARY_BATTLES_BATTLESCENE_H
