#include "battleField.h"
#include "common/utilityModule/stringUtility.h"

using namespace mb::battleModule;
using namespace common::coreModule;

battleField::battleField() {}

void battleField::loadLocation(const std::string& name) {
    const std::string& regionStr = cocos2d::FileUtils::getInstance()->getStringFromFile("properties/nodeProperties/battle/themes/locations.json");
    rapidjson::Document doc;
    doc.Parse<0>(regionStr.c_str());

    if (doc.HasParseError() || doc.IsNull() || !doc.IsObject()) {
        LOG_ERROR("battleField::loadLocation: json parse error");
        return;
    }
    if (!doc.HasMember(name.c_str()) || !doc[name.c_str()].IsObject()) {
        LOG_ERROR(STRING_FORMAT("battleField::loadLocation: location '%s' not found or object is not valid!", name.c_str()));
        return;
    }
    auto data = doc[name.c_str()].GetObject();
    setName(STRING_FORMAT("battlefield_%s", name.c_str()));
    if (data.HasMember("sky") && data["sky"].IsString()) {
        auto skyHolder = new cocos2d::ParallaxNode();
        auto sky = new cocos2d::Node();
        skyHolder->addChild(sky, -1, cocos2d::Vec2(0.05f,0.0f), Vec2::ZERO);
        sky->setName("sky");
        loadProperty(data["sky"].GetString(), sky);
        addChild(skyHolder);
    }
    cocos2d::Node* node = this;
    if (data.HasMember("ground") && data["ground"].IsString()) {
        auto ground = new cocos2d::Node();
        ground->setName("ground");
        loadProperty(data["ground"].GetString(), ground);
        addChild(ground);
        node = ground;
    }
    if (data.HasMember("base") && data["base"].IsString()) {
        baseNode = new node3d();
        baseNode->setName("base");
        loadProperty(data["base"].GetString(), baseNode);
        node->addChild(baseNode);
    } else {
        LOG_ERROR(STRING_FORMAT("battleField::loadLocation: location '%s': base node not exist!", name.c_str()));
        return;
    }
    if (data.HasMember("1stPlan") && data["1stPlan"].IsString()) {
        auto firstPlan = new cocos2d::Node();
        firstPlan->setName("1stPlan");
        loadProperty(data["1stPlan"].GetString(), firstPlan);
        node->addChild(firstPlan);
    }
    if (data.HasMember("baseData") && data["baseData"].IsString()) {
        initBaseData(data["baseData"].GetString());
    }
}
battleField::sBattleFieldData battleField::getBaseData() {
    return baseData;
}

void battleField::initBaseData(const std::string& path) {
    if (path.empty()) {
        LOG_ERROR("battleField::initBaseData: path is empty");
        return;
    }
    const std::string& regionStr = cocos2d::FileUtils::getInstance()->getStringFromFile(STRING_FORMAT("properties/nodeProperties/%s.json", path.c_str()));
    rapidjson::Document doc;
    doc.Parse<0>(regionStr.c_str());

    if (doc.HasParseError() || doc.IsNull() || !doc.IsObject()) {
        LOG_ERROR("battleField::initBaseData: json parse error");
        return;
    }
    auto data = doc.GetObject();
    auto castle = data.FindMember("castle");
    if (castle != data.MemberEnd()) {
        auto x = castle->value.FindMember("x");
        auto y = castle->value.FindMember("y");
        if (x != castle->value.MemberEnd() && x->value.IsNumber()) {
            baseData.castlePos.x = x->value.GetFloat();
        }
        if (y != castle->value.MemberEnd() && y->value.IsNumber()) {
            baseData.castlePos.y = y->value.GetFloat();
        }
    }
    auto builds = data.FindMember("builds");
    if (builds != data.MemberEnd() && builds->value.IsObject()) {
        for (auto it = builds->value.MemberBegin(); it != builds->value.MemberEnd(); ++it) {
            if (it->value.IsObject()) {
                auto pos = cocos2d::Vec2::ZERO;
                auto x = it->value.FindMember("x");
                auto y = it->value.FindMember("y");
                if (x != it->value.MemberEnd() && x->value.IsNumber()) {
                    pos.x = x->value.GetFloat();
                }
                if (y != it->value.MemberEnd() && y->value.IsNumber()) {
                    pos.y = y->value.GetFloat();
                }
                baseData.buildingPos.push_back(pos);
            }
        }
    }

}
