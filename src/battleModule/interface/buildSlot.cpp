#include "buildSlot.h"

using namespace mb::battleModule;

buildSlot::buildSlot() {
    this->setName("buildSlot");
    loadProperty("battle/" + this->getName(), dynamic_cast<cocos2d::Node*>(this));
    setClickAvailable(false);
}

buildSlot::~buildSlot() {}

void buildSlot::setClickAvailable(bool value) {
    if (value) {
        setName("buildSlotGreen");
    } else {
        setName("buildSlotRed");
    }
    loadComponent(this, this->getName());
    setClickable(value);
}
