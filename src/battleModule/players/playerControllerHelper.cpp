#include "playerControllerHelper.h"

using namespace mb::battleModule;

std::pair<ePlayerMoveDirection, ePlayerMoveIntensive> mb::battleModule::getPlayerStateByStick(float x, float y, float distance) {
    auto result = std::pair<ePlayerMoveDirection, ePlayerMoveIntensive>(getPlayerDirectionByStick(x, y), ePlayerMoveIntensive::PLAYER_STOP);
    if ((std::abs(x) > std::abs(distance) * .7f) || (std::abs(y) > std::abs(distance) * .7f)) {
        result.second = ePlayerMoveIntensive::PLAYER_RUN;
    } else if ((std::abs(x) > std::abs(distance) / 3) || (std::abs(y) > std::abs(distance) / 3)) {
        result.second = ePlayerMoveIntensive::PLAYER_WALK;
    }
    return result;
}

ePlayerMoveDirection mb::battleModule::getPlayerDirectionByStick(float x, float y) {
    if (std::abs(x) > std::abs(y)) {
        if (x > 0.f) {
            return ePlayerMoveDirection::RIGHT;
        } else {
            return ePlayerMoveDirection::LEFT;
        }
    } else {
        if (y > 0.f) {
            return ePlayerMoveDirection::UP;
        } else {
            return ePlayerMoveDirection::DOWN;
        }
    }
    return ePlayerMoveDirection::RIGHT;
}
