#ifndef MERCENARY_BATTLES_BUILDSLOT_H
#define MERCENARY_BATTLES_BUILDSLOT_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/soundButton.h"

namespace mb::battleModule {

    class buildSlot : public common::coreModule::soundButton {
      public:
        buildSlot();
        ~buildSlot();

        void setClickAvailable(bool);
    };
}// namespace mb::battleModule

#endif// MERCENARY_BATTLES_BUILDSLOT_H
