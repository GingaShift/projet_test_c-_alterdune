#include "core/GameState.h"

GameState::GameState() {
    reset();
}

void GameState::reset() {
    victories = 0;
    kills = 0;
    spared = 0;
    isRunning = true;
    isGenocideRoute = true;
    playerName = "";
}

void GameState::updateRoute() {
    if (spared > 0) {
        isGenocideRoute = false;
    }
}

bool GameState::isGameOver() const {
    return victories >= 10;
}