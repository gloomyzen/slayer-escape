#ifndef MERCENARY_BATTLES_BATTLEINCOMEWIDGET_H
#define MERCENARY_BATTLES_BATTLEINCOMEWIDGET_H

#include "cocos/ui/CocosGUI.h"
#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace mb::battleModule {

    class battleIncomeWidget
        : public common::coreModule::nodeProperties
        , public cocos2d::Sprite {
      public:
        enum class eIconLabelTypes { GOLD = 0, TROPHIES };
        battleIncomeWidget();
        ~battleIncomeWidget() override;
        CREATE_FUNC(battleIncomeWidget);
        void setIcon(eIconLabelTypes);
        void setData(int);
    };
}// namespace mb::battleModule


#endif// MERCENARY_BATTLES_BATTLEINCOMEWIDGET_H
