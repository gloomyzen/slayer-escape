#ifndef SLAYER_ESCAPE_STICKBUTTON_H
#define SLAYER_ESCAPE_STICKBUTTON_H

#include "cocos/ui/CocosGUI.h"
#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/buttonBase.h"
#include <functional>
#include <map>
#include <string>

namespace mb::battleModule {
    class stickButton
        : public common::coreModule::nodeProperties
        , public common::coreModule::buttonBase {
    public:
        stickButton();
        ~stickButton() override;

        void setStickEnabled(bool value);
        bool getStickEnabled();

    private:
        enum class eActionType { WAIT_AFTER_END_TOUCH = 0 };
        void initController();

        cocos2d::Sprite* btn = nullptr;
        cocos2d::Sprite* smallBtn = nullptr;
        bool stickEnabled = false;
        cocos2d::Vec2 startPos = cocos2d::Vec2::ZERO;

        //settings
        float waitAfterEndTouch = 0.f;
        float stickDistance = 0.f;
        float stickInertionTime = 0.f;
    };
}// namespace mb::battleModule

#endif// SLAYER_ESCAPE_STICKBUTTON_H