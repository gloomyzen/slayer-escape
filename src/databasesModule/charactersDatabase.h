#ifndef MERCENARY_BATTLES_CHARACTERSDATABASE_H
#define MERCENARY_BATTLES_CHARACTERSDATABASE_H

#include "cocos2d.h"
#include "common/databaseModule/databaseInterface.h"
#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include <map>
#include <string>
#include <vector>
#include <tuple>

namespace mb::databasesModule {

    struct sCharacterCraft {
        int cost = 0;
        int trophiesCost = 0;
        float craftTime = 0; //time in seconds
        int income = 0;
    };

    struct sCharacterStats {
        float hp;
        std::pair<float, float> attack; //attack min and max
        float speed = 1.0f; //movement speed
        float attackSpeed = 1.0f;
        sCharacterCraft craft;

        bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject&);
    };

    struct sCharacterData {
        int id;
        std::string bonesString;
        std::string iconPatch;
        sCharacterStats* stats = nullptr;
        bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject&);
    };

    class charactersDatabase : public common::databaseModule::databaseInterface {
      public:
        charactersDatabase();
        ~charactersDatabase();
        void load(const rapidjson::Document&) override;
        const std::map<int, sCharacterData*>& getCharacters() { return charactersDb; }
        sCharacterData* getCharacterById(int);

      private:
        std::map<int, sCharacterData*> charactersDb;
    };
}// namespace mb::databasesModule


#endif// MERCENARY_BATTLES_CHARACTERSDATABASE_H
