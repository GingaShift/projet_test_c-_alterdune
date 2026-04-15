#pragma once
#include "model/enums.h"
#include <string>

class GameState {
public:
    GameState();

    void reset();

    // Compteurs de progression
    int victories;              // Nombre de combats gagnés
    int kills;                  // Monstres tués
    int spared;                 // Monstres épargnés

    // État de la partie
    bool isRunning;
    bool isGenocideRoute;

    // Nom du joueur
    std::string playerName;

    void updateRoute();
    bool isGameOver() const;
};