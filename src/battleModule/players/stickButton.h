#ifndef SLAYER_ESCAPE_STICKBUTTON_H
#define SLAYER_ESCAPE_STICKBUTTON_H

#include "cocos/ui/CocosGUI.h"
#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/buttonBase.h"
#include <functional>

namespace mb::battleModule {
    class stickButton
        : public common::coreModule::nodeProperties
        , public common::coreModule::buttonBase {
      public:
        stickButton();
        ~stickButton() override;
        CREATE_FUNC(stickButton);
    };
}// namespace mb::battleModule

#endif// SLAYER_ESCAPE_STICKBUTTON_H
