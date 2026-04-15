#pragma once
#include "model/enums.h"
#include <string>

class GameState {
public:
    GameState();

    void reset();

    int victories;              // Nombre de combats gagnés
    int kills;                  // Monstres tués
    int spared;                 // Monstres épargnés

    bool isRunning;
    bool isGenocideRoute;

    std::string playerName;

    void updateRoute();
    bool isGameOver() const;
};