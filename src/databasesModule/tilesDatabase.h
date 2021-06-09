#ifndef SLAYER_ESCAPE_TILESDATABASE_H
#define SLAYER_ESCAPE_TILESDATABASE_H


#include "cocos2d.h"
#include "common/databaseModule/databaseInterface.h"
#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include <map>
#include <string>
#include <vector>

namespace mb::databasesModule {

    enum eTileTypes { UNDEFINED = 0, GROUND, WALL, WALL_DESTROY, SPAWN_PLAYER };

    struct sTileData {
        int id;
        std::string nodePath;
        eTileTypes type;
        bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject&);
    };

    class tilesDatabase : public common::databaseModule::databaseInterface {
      public:
        tilesDatabase();
        ~tilesDatabase();
        void load(const rapidjson::Document&) override;
        const std::map<int, sTileData*>& getTiles() { return tilesDb; }
        sTileData* getTileById(int);

      private:
        std::map<int, sTileData*> tilesDb;
    };
}// namespace mb::databasesModule


#endif// SLAYER_ESCAPE_TILESDATABASE_H
