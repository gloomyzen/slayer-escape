#include "battleIncomeWidget.h"
#include "rapidjson//document.h"

using namespace mb::battleModule;

battleIncomeWidget::battleIncomeWidget() {
    this->setName("battleIncomeWidget");
    loadProperty("battle/" + this->getName(), this);
}

battleIncomeWidget::~battleIncomeWidget() {}

void battleIncomeWidget::setIcon(battleIncomeWidget::eIconLabelTypes type) {
    auto settings = getPropertyData().FindMember("settings");
    if (settings != getPropertyData().MemberEnd() && settings->value.IsObject()) {
        std::string icon;
        switch (type) {
        case eIconLabelTypes::GOLD: icon = "gold"; break;
        case eIconLabelTypes::TROPHIES: icon = "trophies"; break;
        }
        auto data = settings->value.GetObject();
        auto it = data.FindMember(icon.c_str());
        if (it != data.MemberEnd() && it->value.IsString()) {
            if (auto sprite = dynamic_cast<cocos2d::Sprite*>(findNode("icon"))) {
                sprite->initWithFile(it->value.GetString());
                loadComponent(sprite);
            }
        }
    }
}
void battleIncomeWidget::setData(int income) {
    if (auto label = dynamic_cast<cocos2d::Label*>(findNode("label"))) {
        if (income < 0) {
            label->setString("0");
        } else if (income >= 10000) {
            label->setString("9999+");
        } else {
            label->setString(std::to_string(income));
        }
    }
}
