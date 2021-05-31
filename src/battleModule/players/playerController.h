#ifndef SLAYER_ESCAPE_PLAYERCONTROLLER_H
#define SLAYER_ESCAPE_PLAYERCONTROLLER_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/signals/signalHolder.h"
#include "playerBase.h"
#include "stickButton.h"

namespace mb::battleModule {
    struct stickButtonEmitter {
        common::signal::signalHolder<> onMove;
        common::signal::signalHolder<> onStop;
    };
    class playerController
        : public cocos2d::Node
        , public common::coreModule::nodeProperties {
    public:
        playerController();
        ~playerController();

        void disableControl();
        void enableControl();

    private:
        void initJoystick();

        bool controlAvailable = false;
        stickButton* joystick = nullptr;
    };
}// namespace mb::battleModule


#endif// SLAYER_ESCAPE_PLAYERCONTROLLER_H
