#ifndef MERCENARY_BATTLES_BATTLEOBJECT_H
#define MERCENARY_BATTLES_BATTLEOBJECT_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/node3d.h"

namespace mb::battleModule {

    class battleObject
        : public common::coreModule::nodeProperties
        , public common::coreModule::node3d {
      public:
        enum class eBattleObjectSize { SMALL = 0, MEDIUM, LARGE };
        battleObject();
        ~battleObject();
        void setObjectSize(eBattleObjectSize);
        cocos2d::Node* getHolder();

      private:
        cocos2d::Node* holder = nullptr;
    };
}// namespace mb::battleModule


#endif// MERCENARY_BATTLES_BATTLEOBJECT_H
