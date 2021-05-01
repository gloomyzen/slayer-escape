#ifndef SLAYER_ESCAPE_PLAYERBASE_H
#define SLAYER_ESCAPE_PLAYERBASE_H


#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include <string>

namespace mb::battleModule {
    class playerBase
        : public common::coreModule::nodeProperties
        , public cocos2d::Sprite {
      public:
        playerBase();
        ~playerBase();

        void initWithId(int);
    };
}// namespace mb::battleModule


#endif// SLAYER_ESCAPE_PLAYERBASE_H
