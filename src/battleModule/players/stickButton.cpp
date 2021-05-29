#include "stickButton.h"

using namespace mb::battleModule;
using namespace cocos2d::ui;

stickButton::stickButton() {
    setFocusEnabled(false);
    setName("stickButton");
    loadProperty("battle/" + this->getName(), this);
    {
        // setup settings
        auto data = getPropertyObject("settings");
        auto item = data.FindMember("waitAfterEndTouch");
        if (item != data.MemberEnd() && item->value.IsNumber()) {
            waitAfterEndTouch = item->value.GetFloat();
        }
        item = data.FindMember("stickXPos");
        if (item != data.MemberEnd() && item->value.IsArray()) {
            auto array = item->value.GetArray();
            stickXPos = { array[0].GetFloat(), array[1].GetFloat() };
        }
        item = data.FindMember("stickYPos");
        if (item != data.MemberEnd() && item->value.IsArray()) {
            auto array = item->value.GetArray();
            stickYPos = { array[0].GetFloat(), array[1].GetFloat() };
        }
    }

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
            smallBtn->setPosition(cocos2d::Vec2::ZERO);
        } break;
        case Widget::TouchEventType::MOVED: {
            // todo startPos - new position
            auto movePos = getTouchMovePosition();
            auto newPos = cocos2d::Vec2(movePos.x - startPos.x, movePos.y - startPos.y);
            if (std::abs(newPos.distance(cocos2d::Vec2::ZERO)) >= 44) {
//                newPos = smallBtn->getPosition();
                if (newPos.x > stickXPos.first)
                    newPos.x = stickXPos.first;
                if (newPos.x < stickXPos.second)
                    newPos.x = stickXPos.second;
                if (newPos.y > stickYPos.first)
                    newPos.y = stickYPos.first;
                if (newPos.y < stickYPos.second)
                    newPos.y = stickYPos.second;
            }
            smallBtn->setPosition(newPos);
        } break;
        case Widget::TouchEventType::ENDED:
        case Widget::TouchEventType::CANCELED: {
            {
                // action move btn to start position
                // todo uncomment after testing
                auto delay = cocos2d::DelayTime::create(waitAfterEndTouch);
                auto clb = cocos2d::CallFunc::create([this]() {
                    btn->setPosition(cocos2d::Vec2::ZERO);
                    smallBtn->setPosition(cocos2d::Vec2::ZERO);
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
