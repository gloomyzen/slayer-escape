#ifdef DEBUG

#include "heroProfileDebug.h"
#include "cocos2d.h"
#include "common/profileModule/profileManager.h"
#include "common/utilityModule/stringUtility.h"
#include "databasesModule/charactersDatabase.h"
#include "databasesModule/databaseManager.h"
#include "ImGuiEXT/imgui/imgui.h"
#include "ImGuiEXT/imgui/imgui_internal.h"
#include <localProfile/heroesProfileBlock.h>

using namespace mb::debugProfile;


heroProfileDebug::heroProfileDebug() {}
heroProfileDebug::~heroProfileDebug() {}

heroProfileDebug* currentProfileDebugger = nullptr;

heroProfileDebug& heroProfileDebug::getInstance() {
    if (currentProfileDebugger == nullptr) {
        currentProfileDebugger = new heroProfileDebug();
    }
    return *currentProfileDebugger;
}

void heroProfileDebug::update() {
    if (ImGui::Button("Heroes")) {
        isOpened = !isOpened;
    }
    if (isOpened) {
        profileWindow(&isOpened);
    }
}

void heroProfileDebug::profileWindow(bool* windowOpened) {
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(400), static_cast<float>(350)),
                             ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Heroes database", reinterpret_cast<bool*>(windowOpened))) {
        ImGui::End();
        return;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::Columns(2, "AB");

    ImGui::BeginChild("left");
    leftList();
    ImGui::EndChild();

    ImGui::NextColumn();

    ImGui::BeginChild("right");
    rightData();
    ImGui::EndChild();

    ImGui::PopStyleVar();
    ImGui::End();
}

void heroProfileDebug::leftList() {
    using namespace databasesModule;
    auto characterDb = GET_DATABASE_MANAGER().getDatabase<charactersDatabase>(databaseManager::eDatabaseList::CHARACTER_DB);
    auto profile = GET_PROFILE().getBlock<localProfile::heroesProfileBlock>("heroes");
    for (const auto& item : characterDb->getCharacters()) {
        std::string str;
        if (profile->hasHero(item.second->id)) {
            str = STRING_FORMAT("%d +", item.second->id);
        } else {
            str = STRING_FORMAT("%d", item.second->id);
        }
        if (ImGui::ButtonEx(str.c_str(), ImVec2(0, 0), ImGuiButtonFlags_AlignTextBaseLine | ImGuiButtonFlags_NoHoveredOnFocus)) {
            lastOpenedHero = item.second->id;
        }
    }
}

void heroProfileDebug::rightData() {
    using namespace databasesModule;
    if (lastOpenedHero == -1) return;
    auto characterDb = GET_DATABASE_MANAGER().getDatabase<charactersDatabase>(databaseManager::eDatabaseList::CHARACTER_DB);
    auto character = characterDb->getCharacterById(lastOpenedHero);
    if (!character) return;

    auto profile = GET_PROFILE().getBlock<localProfile::heroesProfileBlock>("heroes");

    ImGui::Text("Character id %d", character->id);
    ImGui::Text("Icon path %s", character->iconPatch.c_str());
    ImGui::Text("Bones path %s", character->bonesString.c_str());

    if (profile->hasHero(lastOpenedHero)) {
        if (ImGui::ButtonEx("remove hero", ImVec2(0, 0), ImGuiButtonFlags_AlignTextBaseLine | ImGuiButtonFlags_NoHoveredOnFocus)) {
            profile->removeHero(lastOpenedHero);
        }
    }

    if (!profile->hasHero(lastOpenedHero)) {
        if (ImGui::ButtonEx("add hero", ImVec2(0, 0), ImGuiButtonFlags_AlignTextBaseLine | ImGuiButtonFlags_NoHoveredOnFocus)) {
            profile->addHero(lastOpenedHero);
        }
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::CollapsingHeader("Stats")) {
        float hp = character->stats->hp;
        ImGui::DragFloat("Hp", &hp, 0.1, 0.1);
        if (hp != character->stats->hp) {
            character->stats->hp = hp;
        }

        float speed = character->stats->speed;
        ImGui::DragFloat("Speed", &speed, 0.1, 0.1);
        if (speed != character->stats->speed) {
            character->stats->speed = speed;
        }

        float attack[2] = {character->stats->attack.first, character->stats->attack.second};
        ImGui::DragFloat2("Attack", attack, 0.1, 0.1);
        if (attack[0] != character->stats->attack.first || attack[1] != character->stats->attack.second) {
            character->stats->attack.first = attack[0];
            character->stats->attack.second = attack[1];
        }

        float attackSpeed = character->stats->attackSpeed;
        ImGui::DragFloat("Attack speed", &attackSpeed, 0.1, 0.1);
        if (attackSpeed != character->stats->attackSpeed) {
            character->stats->attackSpeed = attackSpeed;
        }
    }
    if (ImGui::CollapsingHeader("Craft stats")) {
        float craftTime = character->stats->craft.craftTime;
        ImGui::DragFloat("Craft time", &craftTime, 0.1, 0.1);
        if (craftTime != character->stats->craft.craftTime) {
            character->stats->craft.craftTime = craftTime;
        }

        int income = character->stats->craft.income;
        ImGui::DragInt("Income", &income, 1, 0);
        if (income != character->stats->craft.income) {
            character->stats->craft.income = income;
        }

        int cost = character->stats->craft.cost;
        ImGui::DragInt("Craft cost", &cost, 1, 0);
        if (cost != character->stats->craft.cost) {
            character->stats->craft.cost = cost;
        }

        int trophiesCost = character->stats->craft.trophiesCost;
        ImGui::DragInt("Craft trophies cost", &trophiesCost, 1, 0);
        if (trophiesCost != character->stats->craft.trophiesCost) {
            character->stats->craft.trophiesCost = trophiesCost;
        }
    }

}

#endif