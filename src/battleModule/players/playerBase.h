#ifndef SLAYER_ESCAPE_PLAYERBASE_H
#define SLAYER_ESCAPE_PLAYERBASE_H


#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databasesModule/charactersDatabase.h"
#include "battleModule/players/playerControllerHelper.h"
#include <string>

namespace mb::battleModule {
    class playerBase
        : public common::coreModule::nodeProperties
        , public cocos2d::Node {
      public:
        playerBase();
        ~playerBase();

        static playerBase* initWithId(int);
        void loadData(databasesModule::sCharacterData* data);



    private:
        databasesModule::sCharacterData* characterData = nullptr;
        ePlayerMoveXDirection playerDirection = ePlayerMoveXDirection::RIGHT;
    };
}// namespace mb::battleModule


#endif// SLAYER_ESCAPE_PLAYERBASE_H
