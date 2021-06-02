#ifndef SLAYER_ESCAPE_PLAYERCONTROLLERHELPER_H
#define SLAYER_ESCAPE_PLAYERCONTROLLERHELPER_H

#include <tuple>
#include <string>

namespace mb::battleModule {
    enum class ePlayerMoveDirection {
        LEFT = 0,
        UP,
        RIGHT,
        BOTTOM
    };
    enum class ePlayerMoveIntensive {
        PLAYER_STOP = 0,
        PLAYER_WALK,
        PLAYER_RUN
    };

    std::pair<ePlayerMoveDirection, ePlayerMoveIntensive> getPlayerStateByStick(float x, float y, float distance);

    ePlayerMoveDirection getPlayerDirectionByStick(float x, float y);
}

#endif// SLAYER_ESCAPE_PLAYERCONTROLLERHELPER_H
