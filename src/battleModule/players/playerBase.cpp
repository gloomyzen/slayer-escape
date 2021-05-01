#include "playerBase.h"
#include <databasesModule/charactersDatabase.h>
#include <databasesModule/databaseManager.h>

using namespace mb::battleModule;

playerBase::playerBase() {}

playerBase* playerBase::initWithId(int id) {
    playerBase* player;
    auto characterDb = GET_DATABASE_MANAGER().getDatabase<databasesModule::charactersDatabase>(databasesModule::databaseManager::eDatabaseList::CHARACTER_DB);
    auto data = characterDb->getCharacterById(id);
    if (data->isSpine) {
        player = dynamic_cast<playerBase*>(new playerSprite());
    } else {
        //todo add spine node when spine is be ready
        player = dynamic_cast<playerBase*>(new playerSprite());
    }
    player->setName("unit");
    player->loadProperty(data->propertyPath, player);

    return player;
}

playerBase::~playerBase() = default;


