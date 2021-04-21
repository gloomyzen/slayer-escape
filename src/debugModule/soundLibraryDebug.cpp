#ifdef DEBUG

#include "soundLibraryDebug.h"
#include "cocos2d.h"
#include "ImGuiEXT/imgui/imgui.h"
#include "ImGuiEXT/imgui/imgui_internal.h"
#include "common/audioModule/audioEngine.h"

using namespace mb::debugProfile;


soundLibraryDebug::soundLibraryDebug() {}
soundLibraryDebug::~soundLibraryDebug() {}

soundLibraryDebug* currentSoundDebugger = nullptr;

soundLibraryDebug& soundLibraryDebug::getInstance() {
    if (currentSoundDebugger == nullptr) {
        currentSoundDebugger = new soundLibraryDebug();
    }
    return *currentSoundDebugger;
}

void soundLibraryDebug::update() {
    if (ImGui::Button("Sounds")) {
        isOpened = !isOpened;
    }
    if (isOpened) {
        soundWindow(&isOpened);
    }
}

void soundLibraryDebug::soundWindow(bool* windowOpened) {
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(400), static_cast<float>(350)),
                             ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Sounds debug", reinterpret_cast<bool*>(windowOpened))) {
        ImGui::End();
        return;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    ImGui::BeginChild("sounds");
    ImGui::PushID("sounds");

    auto effects = GET_AUDIO_ENGINE().getAllSounds();
    const char* items[effects.size()];
    static int currentEffect = 0;
    int countEffects = 0;
    std::for_each(effects.begin(), effects.end(), [&items, &countEffects](const auto& effect){
           items[countEffects] = effect.first.c_str();
           countEffects++;
    });

    ImGui::Combo("Effects", &currentEffect, items, IM_ARRAYSIZE(items));
    if (ImGui::Button("Play effect") && currentEffect >= 0 && currentEffect < static_cast<int>(effects.size())) {
        GET_AUDIO_ENGINE().play(items[currentEffect]);
    }


    ImGui::PopID();
    ImGui::EndChild();

    ImGui::PopStyleVar();
    ImGui::End();
}

#endif