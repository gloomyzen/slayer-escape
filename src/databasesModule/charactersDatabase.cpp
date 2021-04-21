#include "charactersDatabase.h"
#include "common/coreModule/resources/resourceManager.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"

using namespace mb::databasesModule;

charactersDatabase::charactersDatabase() {}

charactersDatabase::~charactersDatabase() {
    for (auto& [_, db] : charactersDb) {
        delete db;
        db = nullptr;
    }
}
void charactersDatabase::load(const rapidjson::Document& json) {
    if (getPath().empty()) {
        LOG_ERROR("charactersDatabase::load: path is empty!");
        return;
    }
    if (!json.IsObject()) {
        LOG_ERROR(STRING_FORMAT("charactersDatabase::load: file from path '%s' is not object!", getPath().c_str()));
        return;
    }
    auto characters = json.FindMember("characters");
    if (characters != json.MemberEnd() && characters->value.IsObject()) {
        auto object = characters->value.GetObject();
        for (auto characterIt = object.MemberBegin(); characterIt != object.MemberEnd(); ++characterIt) {
            if (characterIt->name.IsString() && characterIt->value.IsObject()) {
                auto tempId = characterIt->name.GetString();
                auto item = new sCharacterData();
                item->id = std::atoi(tempId);
                if (item->load(characterIt->value.GetObject())) {
                    charactersDb.insert({item->id, item});
                }
            } else {
                LOG_ERROR(STRING_FORMAT("charactersDatabase::load: file from path '%s' has errors!", getPath().c_str()));
            }
        }
    }
}

sCharacterData* charactersDatabase::getCharacterById(int id) {
    auto find = charactersDb.find(id);
    if (find != charactersDb.end()) {
        return find->second;
    }
    return nullptr;
}

bool sCharacterData::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& object) {
    auto loadStats = new sCharacterStats();
    if (loadStats->load(object)) {
        stats = loadStats;
    } else {
        return false;
    }
    if (object.HasMember("propertyPath") && object["propertyPath"].IsString()) bonesString = object["propertyPath"].GetString();
    if (object.HasMember("iconPath") && object["iconPath"].IsString()) iconPatch = object["iconPath"].GetString();
    return true;
}

bool sCharacterStats::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& object) {
    if (object.HasMember("hp") && object["hp"].IsNumber()) {
        hp = object["hp"].GetFloat();
    } else {
        return false;
    }
    if (object.HasMember("attackMin") && object.HasMember("attackMax") && object["attackMin"].IsNumber() && object["attackMax"].IsNumber()) {
        attack = std::make_pair(object["attackMin"].GetFloat(), object["attackMax"].GetFloat());
    } else {
        return false;
    }
    if (object.HasMember("speed") && object["speed"].IsNumber()) speed = object["speed"].GetFloat();
    if (object.HasMember("attackSpeed") && object["attackSpeed"].IsNumber()) attackSpeed = object["attackSpeed"].GetFloat();

    if (object.HasMember("cost") && object["cost"].IsNumber()) craft.cost = object["cost"].GetInt();
    if (object.HasMember("trophiesCost") && object["trophiesCost"].IsNumber()) craft.trophiesCost = object["trophiesCost"].GetInt();
    if (object.HasMember("craftTime") && object["craftTime"].IsNumber()) craft.craftTime = object["craftTime"].GetInt();
    if (object.HasMember("income") && object["income"].IsNumber()) craft.income = object["income"].GetInt();
    return true;
}
