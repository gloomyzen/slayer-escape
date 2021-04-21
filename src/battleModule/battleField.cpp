#include "battleField.h"
#include "common/debugModule/logManager.h"
#include "databasesModule/databaseManager.h"
#include "databasesModule/mapsDatabase.h"
#include <map>
#include <tuple>

using namespace mb::battleModule;

battleField::battleField() {
    this->setName("battleField");
//    loadProperty("scenes/" + this->getName(), dynamic_cast<Node*>(this));
}

battleField::~battleField() {}

void battleField::initLayer(int id) {
    using namespace databasesModule;
    //generate a maze
    auto mapsDb = GET_DATABASE_MANAGER().getDatabase<mapsDatabase>(databaseManager::eDatabaseList::MAPS_DB);
    auto map = mapsDb->getMapById(id);
    if (map == nullptr) {
        //todo log error
        return;
    }
    std::map<std::pair<int, int>, cocos2d::Node*> result;
    //todo wip
}
