#ifndef MERCENARY_BATTLES_BATTLEFIELD_H
#define MERCENARY_BATTLES_BATTLEFIELD_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/node3d.h"
#include <string>
#include <vector>

namespace mb::battleModule {
    class battleField
        : public common::coreModule::nodeProperties
        , public cocos2d::Node {
      public:
        struct sBattleFieldData {
            cocos2d::Vec2 castlePos;
            std::vector<cocos2d::Vec2> buildingPos;
        };
        battleField();
        ~battleField() = default;
        void loadLocation(const std::string&);
        common::coreModule::node3d* getBaseNode() { return baseNode; }
        sBattleFieldData getBaseData();

      private:
        void initBaseData(const std::string&);

        common::coreModule::node3d* baseNode = nullptr;
        sBattleFieldData baseData;
    };
}// namespace mb::battleModule


#endif// MERCENARY_BATTLES_BATTLEFIELD_H
