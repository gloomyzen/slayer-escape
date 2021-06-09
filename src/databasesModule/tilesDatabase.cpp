#include "tilesDatabase.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"
#include <map>

using namespace mb::databasesModule;

const std::map<std::string, eTileTypes> tileTypesMap = {
    {"ground", eTileTypes::GROUND},
    {"wall", eTileTypes::WALL},
    {"wallDestroy", eTileTypes::WALL_DESTROY},
    {"spawnPlayer", eTileTypes::SPAWN_PLAYER}
};

tilesDatabase::tilesDatabase() {}

tilesDatabase::~tilesDatabase() {
    for (auto& [_, db] : tilesDb) {
        delete db;
        db = nullptr;
    }
}

void tilesDatabase::load(const rapidjson::Document& json) {
    if (getPath().empty()) {
        LOG_ERROR("tilesDatabase::load: path is empty!");
        return;
    }
    if (!json.IsObject()) {
        LOG_ERROR(STRING_FORMAT("tilesDatabase::load: file from path '%s' is not object!", getPath().c_str()));
        return;
    }
    auto tiles = json.FindMember("tiles");
    if (tiles != json.MemberEnd() && tiles->value.IsObject()) {
        auto object = tiles->value.GetObject();
        for (auto characterIt = object.MemberBegin(); characterIt != object.MemberEnd(); ++characterIt) {
            if (characterIt->name.IsString() && characterIt->value.IsObject()) {
                auto tempId = characterIt->name.GetString();
                auto item = new sTileData();
                item->id = std::atoi(tempId);
                if (item->load(characterIt->value.GetObject())) {
                    tilesDb.insert({item->id, item});
                }
            } else {
                LOG_ERROR(STRING_FORMAT("tilesDatabase::load: file from path '%s' has errors!", getPath().c_str()));
            }
        }
    }
}

sTileData* tilesDatabase::getTileById(int id) {
    auto find = tilesDb.find(id);
    if (find != tilesDb.end()) {
        return find->second;
    }
    return nullptr;
}

bool sTileData::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& object) {
    if (object.HasMember("propertyPath") && object["propertyPath"].IsString()) nodePath = object["propertyPath"].GetString();
    if (object.HasMember("type") && object["type"].IsString()) {
        auto find = tileTypesMap.find(object["type"].GetString());
        if (find != tileTypesMap.end()) {
            type = find->second;
        } else {
            type = eTileTypes::UNDEFINED;
        }
    }

    return true;
}