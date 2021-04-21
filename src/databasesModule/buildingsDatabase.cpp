#include "buildingsDatabase.h"
#include "common/utilityModule/stringUtility.h"

using namespace mb::databasesModule;

buildingsDatabase::buildingsDatabase() {}

buildingsDatabase::~buildingsDatabase() {
    for (auto& [_, db] : buildingsDb) {
        delete db;
        db = nullptr;
    }
}
void buildingsDatabase::load(const rapidjson::Document& json) {
    if (getPath().empty()) {
        LOG_ERROR("buildingsDatabase::load: path is empty!");
        return;
    }
    if (!json.IsObject()) {
        LOG_ERROR(STRING_FORMAT("buildingsDatabase::load: file from path '%s' is not object!", getPath().c_str()));
        return;
    }
    auto buildings = json.FindMember("buildings");
    if (buildings != json.MemberEnd() && buildings->value.IsObject()) {
        auto object = buildings->value.GetObject();
        for (auto buildIt = object.MemberBegin(); buildIt != object.MemberEnd(); ++buildIt) {
            if (buildIt->name.IsString() && buildIt->value.IsObject()) {
                auto tempId = buildIt->name.GetString();
                auto item = new sBuildData();
                item->id = std::atoi(tempId);
                if (item->load(buildIt->value.GetObject())) {
                    buildingsDb.insert({ item->id, item });
                }
            } else {
                LOG_ERROR(
                    STRING_FORMAT("charactersDatabase::load: file from path '%s' has errors!", getPath().c_str()));
            }
        }
    }
}

sBuildData* buildingsDatabase::getBuildById(int id) {
    auto find = buildingsDb.find(id);
    if (find != buildingsDb.end()) {
        return find->second;
    }
    return nullptr;
}

bool sBuildData::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& object) {
    if (object.HasMember("level") && object["level"].IsNumber()) level = object["level"].GetInt();
    if (object.HasMember("unitIdA") && object["unitIdA"].IsNumber()) unitIdA = object["unitIdA"].GetInt();
    if (object.HasMember("unitIdB") && object["unitIdB"].IsNumber()) unitIdB = object["unitIdB"].GetInt();
    if (object.HasMember("propertyPath") && object["propertyPath"].IsString()) propertyPath = object["propertyPath"].GetString();
    return true;
}
