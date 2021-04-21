#ifndef MERCENARY_BATTLES_BUILDINGSDATABASE_H
#define MERCENARY_BATTLES_BUILDINGSDATABASE_H

#include "cocos2d.h"
#include "common/databaseModule/databaseInterface.h"
#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include <map>
#include <string>

namespace mb::databasesModule {

    struct sBuildData {
        int id;
        int level = 1;
        int unitIdA = 0;
        int unitIdB = 0;
        std::string propertyPath;
        bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject&);
    };

    class buildingsDatabase : public common::databaseModule::databaseInterface {
      public:
        buildingsDatabase();
        ~buildingsDatabase();
        void load(const rapidjson::Document&) override;
        const std::map<int, sBuildData*>& getBuildings() { return buildingsDb; }
        sBuildData* getBuildById(int);

      private:
        std::map<int, sBuildData*> buildingsDb;
    };
}


#endif// MERCENARY_BATTLES_BUILDINGSDATABASE_H
