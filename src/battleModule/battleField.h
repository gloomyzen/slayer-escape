#ifndef SLAYER_ESCAPE_BATTLEFIELD_H
#define SLAYER_ESCAPE_BATTLEFIELD_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace mb::battleModule {
    class battleField
        : public common::coreModule::nodeProperties
        , public cocos2d::Node {
      public:
        battleField();
        ~battleField();

        void setLayer(cocos2d::Layer* layer) { world = layer; }

        void initLayer(int);

      private:
        cocos2d::Layer* world = nullptr;
    };
}// namespace mb::battleModule


#endif// SLAYER_ESCAPE_BATTLEFIELD_H
