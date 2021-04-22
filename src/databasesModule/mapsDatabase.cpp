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
    if (object.HasMember("map") && object["map"].IsArray()) {
        int x = 0;
        int y = 0;
        for (const auto& row : object["map"].GetArray()) {
            if (row.IsArray()) {
                y = 0;
                for (const auto& col : row.GetArray()) {
                    if (col.IsObject()) {
                        //todo add
                        if (col.HasMember("piece") && col["piece"].IsNumber()) {
                            map[x][y] = col["piece"].GetInt();
                        }
                        ++y;
                    }
                }
                ++x;
            }
        }
    }
    return true;
}
