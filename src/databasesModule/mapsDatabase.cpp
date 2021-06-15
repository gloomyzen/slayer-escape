#include "mapsDatabase.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"
#include <map>

using namespace mb::databasesModule;

mapsDatabase::mapsDatabase() {}

mapsDatabase::~mapsDatabase() {
    for (auto& [_, db] : mapsDb) {
        delete db;
        db = nullptr;
    }
}

void mapsDatabase::load(const rapidjson::Document& json) {
    if (getPath().empty()) {
        LOG_ERROR("mapsDatabase::load: path is empty!");
        return;
    }
    if (!json.IsObject()) {
        LOG_ERROR(STRING_FORMAT("mapsDatabase::load: file from path '%s' is not object!", getPath().c_str()));
        return;
    }
    auto tiles = json.FindMember("maps");
    if (tiles != json.MemberEnd() && tiles->value.IsObject()) {
        auto object = tiles->value.GetObject();
        for (auto characterIt = object.MemberBegin(); characterIt != object.MemberEnd(); ++characterIt) {
            if (characterIt->name.IsString() && characterIt->value.IsObject()) {
                auto tempId = characterIt->name.GetString();
                auto item = new sMapData();
                item->id = std::atoi(tempId);
                if (item->load(characterIt->value.GetObject())) {
                    mapsDb.insert({item->id, item});
                }
            } else {
                LOG_ERROR(STRING_FORMAT("mapsDatabase::load: file from path '%s' has errors!", getPath().c_str()));
            }
        }
    }
}

sMapData* mapsDatabase::getMapById(int id) {
    auto find = mapsDb.find(id);
    if (find != mapsDb.end()) {
        return find->second;
    }
    return nullptr;
}

bool sMapData::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& object) {
    if (object.HasMember("mapPath") && object["mapPath"].IsString()) {
        mapPath = object["mapPath"].GetString();
    } else {
        LOG_ERROR("sMapData::load: missing property 'mapPath'!");
        return false;
    }
    if (object.HasMember("wallsObject") && object["wallsObject"].IsString()) {
        wallsObject = object["wallsObject"].GetString();
    } else {
        LOG_ERROR("sMapData::load: missing property 'wallsObject'!");
        return false;
    }
    if (object.HasMember("groundGroup") && object["groundGroup"].IsString()) {
        groundGroup = object["groundGroup"].GetString();
    } else {
        LOG_ERROR("sMapData::load: missing property 'groundGroup'!");
        return false;
    }
    if (object.HasMember("spawnPlayerProperty") && object["spawnPlayerProperty"].IsString()) {
        spawnPlayerProperty = object["spawnPlayerProperty"].GetString();
    } else {
        LOG_ERROR("sMapData::load: missing property 'spawnPlayerProperty'!");
        return false;
    }
    if (object.HasMember("spawnEnemyProperty") && object["spawnEnemyProperty"].IsString()) {
        spawnEnemyProperty = object["spawnEnemyProperty"].GetString();
    } else {
        LOG_ERROR("sMapData::load: missing property 'spawnEnemyProperty'!");
        return false;
    }
    return true;
}
