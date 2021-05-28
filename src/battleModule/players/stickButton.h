#ifndef SLAYER_ESCAPE_STICKBUTTON_H
#define SLAYER_ESCAPE_STICKBUTTON_H

#include "cocos/ui/CocosGUI.h"
#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/buttonBase.h"
#include <functional>
#include <string>
#include <map>

namespace mb::battleModule {
    class stickButton
        : public common::coreModule::nodeProperties
        , public common::coreModule::buttonBase {
    public:
        enum class eStickType { BIG_STICK, SMALL_STICK };

        stickButton(eStickType type);
        ~stickButton() override;

    private:
        void initController();

        eStickType stickType = eStickType::SMALL_STICK;
        static std::map<eStickType, std::string> stickButtonTypes;
    };
}// namespace mb::battleModule

#endif// SLAYER_ESCAPE_STICKBUTTON_H
