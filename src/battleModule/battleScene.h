#ifndef MERCENARY_BATTLES_BATTLESCENE_H
#define MERCENARY_BATTLES_BATTLESCENE_H

#include "battleModule/battleField.h"
#include "battleModule/playerData/playerData.h"
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

        void onBuildClick(sPlayerBuild&);

      private:
        battleField* battleFieldNode = nullptr;
        // world section
        cocos2d::Layer* world = nullptr;
        std::pair<playerData*, playerData*> player;
        int gold = 100;
        int trophies = 0;
    };
}// namespace mb::battleModule


#endif// MERCENARY_BATTLES_BATTLESCENE_H
