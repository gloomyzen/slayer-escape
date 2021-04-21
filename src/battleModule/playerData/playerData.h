#ifndef MERCENARY_BATTLES_PLAYERDATA_H
#define MERCENARY_BATTLES_PLAYERDATA_H

#include "battleModule/battleField.h"
#include "battleModule/battleObject.h"
#include "battleModule/interface/buildSlot.h"
#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/node3d.h"
#include <map>
#include <string>

namespace mb::battleModule {

    enum class ePlayerPosition { LEFT = 0, RIGHT };
    enum class ePlayerMode { PVE = 0, PVP };
    enum class ePlayerFraction { HUMAN = 0, ORC };

    static const std::map<ePlayerFraction, std::string> fractionNames = {
        { ePlayerFraction::ORC, "orc" },
        { ePlayerFraction::HUMAN, "human" },
    };

    struct sPlayerBuild {
        int level = 0;
        buildSlot* slot = nullptr;
        cocos2d::Vec2 pos;
    };

    class playerData {
      public:
        playerData();
        ~playerData();

        void setPlayerPosition(ePlayerPosition value) { playerPosition = value; }
        ePlayerPosition getPLayerPosition() { return playerPosition; }
        void setPlayerMode(ePlayerMode value) { playerMode = value; }
        ePlayerMode getPlayerMode() { return playerMode; }
        void setPlayerFraction(ePlayerFraction value) { playerFraction = value; }
        ePlayerFraction getPlayerFraction() { return playerFraction; }
        void setRealUser(bool value) { isRealUser = value; }
        bool getRealUser() const { return isRealUser; }
        void setBattleField(battleField* value) { bf = value; }

        void init();

        std::map<int, sPlayerBuild> &getPlayerBuilds() { return playerBuilds; };

      private:
        void initCastle();
        void initBuilds();

        ePlayerPosition playerPosition = ePlayerPosition::LEFT;
        ePlayerMode playerMode = ePlayerMode::PVE;
        ePlayerFraction playerFraction = ePlayerFraction::HUMAN;
        bool isRealUser = false;
        battleField* bf = nullptr;// is not owner
        battleObject* castle = nullptr;
        bool inited = false;
        std::map<int, sPlayerBuild> playerBuilds;
    };
}// namespace mb::battleModule


#endif// MERCENARY_BATTLES_PLAYERDATA_H
