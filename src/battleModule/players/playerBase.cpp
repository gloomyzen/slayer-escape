#include "playerBase.h"
#include <databasesModule/charactersDatabase.h>
#include <databasesModule/databaseManager.h>

using namespace mb::battleModule;

playerBase::playerBase() {}

void playerBase::initWithId(int id) {
    auto characterDb = GET_DATABASE_MANAGER().getDatabase<databasesModule::charactersDatabase>(databasesModule::databaseManager::eDatabaseList::CHARACTER_DB);
    auto data = characterDb->getCharacterById(id);
    data.
}

playerBase::~playerBase() = default;


