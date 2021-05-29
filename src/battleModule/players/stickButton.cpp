#include "stickButton.h"

using namespace mb::battleModule;
using namespace cocos2d::ui;

stickButton::stickButton() {
    setFocusEnabled(false);
    setName("stickButton");
    loadProperty("battle/" + this->getName(), this);
    setStickEnabled(true);
    initController();
}

void stickButton::initController() {
    if (auto bgNode = findNode("buttonNode")) {
        btn = cocos2d::Sprite::create();
        btn->setName("stickSmallBtn");
        loadComponent(btn);
        bgNode->addChild(btn);
    }
    addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
           switch (type) {
           case Widget::TouchEventType::BEGAN: {

               auto pos = getTouchBeganPosition();
               setPosition(pos);
           } break;
           case Widget::TouchEventType::MOVED: {
               //
           } break;
           case Widget::TouchEventType::ENDED:
           case Widget::TouchEventType::CANCELED: {
                //
               return true;
           } break;
           default:
               break;
           }
           return true;
    });
}

void stickButton::setStickEnabled(bool value) {
    stickEnabled = value;
    setTouchEnabled(stickEnabled);
}

bool stickButton::getStickEnabled() {
    return stickEnabled;
}

stickButton::~stickButton() = default;
