#ifndef SLAYER_ESCAPE_MAPTILE_H
#define SLAYER_ESCAPE_MAPTILE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include <string>

namespace mb::battleModule {
    class mapTile
        : public common::coreModule::nodeProperties
        , public cocos2d::Sprite {
      public:
        mapTile();
        ~mapTile();
        void initWithProp(const std::string& name, const std::string& path);
    };
}// namespace mb::battleModule


#endif// SLAYER_ESCAPE_MAPTILE_H
