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
    btn = dynamic_cast<cocos2d::Sprite*>(findNode("buttonNode"));
    if (btn) {
        smallBtn = cocos2d::Sprite::create();
        smallBtn->setName("stickSmallBtn");
        loadComponent(smallBtn);
        btn->addChild(smallBtn);
    }
    addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
        case Widget::TouchEventType::BEGAN: {
            {
                // break active actions
                stopAllActionsByTag(static_cast<int>(stickButton::eActionType::WAIT_AFTER_END_TOUCH));
            }
            startPos = getTouchBeganPosition();
            auto newPos = cocos2d::Vec2(startPos.x - btn->getContentSize().width / 2,
                                        startPos.y - btn->getContentSize().height / 2);
            btn->setPosition(newPos);
        } break;
        case Widget::TouchEventType::MOVED: {
            //todo startPos - new position
        } break;
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED: {
            {
                // action move btn to start position
                auto delay = cocos2d::DelayTime::create(2.f);
                auto clb = cocos2d::CallFunc::create([this]() {
                    btn->setPosition(cocos2d::Vec2::ZERO);
                });
                auto seq = cocos2d::Sequence::create(delay, clb, nullptr);
                seq->setTag(static_cast<int>(stickButton::eActionType::WAIT_AFTER_END_TOUCH));
                runAction(seq);
            }
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
