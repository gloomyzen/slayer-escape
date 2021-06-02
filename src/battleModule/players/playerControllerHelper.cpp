#include "playerControllerHelper.h"

using namespace mb::battleModule;

std::pair<ePlayerMoveDirection, ePlayerMoveIntensive> mb::battleModule::getPlayerStateByStick(float x, float y, float distance) {
    if ((std::abs(x) < std::abs(distance) / 3) && (std::abs(y) < std::abs(distance) / 3)) {
        return std::pair<ePlayerMoveDirection, ePlayerMoveIntensive>(ePlayerMoveDirection::BOTTOM, ePlayerMoveIntensive::PLAYER_STOP);
    }
    return std::pair<ePlayerMoveDirection, ePlayerMoveIntensive>();
}
ePlayerMoveDirection mb::battleModule::getPlayerDirectionByStick(float x, float y) {

    return ePlayerMoveDirection::LEFT;
}
