#include "databaseTool.h"

using namespace mb::databasesModule;

std::pair<sCharacterData*, sCharacterData*> databaseTool::getCharacterByBuilding(int id) {
    auto result = std::pair<sCharacterData*, sCharacterData*>();
    auto buildsDb = GET_DATABASE_MANAGER().getDatabase<buildingsDatabase>(databaseManager::eDatabaseList::BUILDING_DB);
    auto characterDb = GET_DATABASE_MANAGER().getDatabase<charactersDatabase>(databaseManager::eDatabaseList::CHARACTER_DB);
    if (auto building = buildsDb->getBuildById(id)) {
        result.first = characterDb->getCharacterById(building->unitIdA);
        result.second = characterDb->getCharacterById(building->unitIdB);
    }

    return result;
}
