#include "stickButton.h"

using namespace mb::battleModule;

std::map<stickButton::eStickType, std::string> stickButton::stickButtonTypes = {
    {eStickType::BIG_STICK, "stickBigCircle"},
    {eStickType::SMALL_STICK, "stickSmallCircle"}
};

stickButton::stickButton(eStickType type) {
    setFocusEnabled(false);
    stickType = type;
    initController();
}

void stickButton::initController() {
    setName(stickButtonTypes[stickType]);
    loadProperty("battle/" + this->getName(), this);
}

stickButton::~stickButton() = default;
