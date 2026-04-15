#pragma once
#include "core/GameState.h"
#include "model/Player.h"
#include "systems/Bestiary.h"
#include "systems/ActCatalog.h"
#include "systems/CombatSystem.h"
#include "systems/EndingSystem.h"
#include "ui/Menu.h"
#include "ui/Display.h"
#include <memory>

class Game {
public:
    // Constructeur
    Game();

    // Lance le jeu — boucle principale
    void run();

private:
    // --- Systèmes ---
    GameState           state;
    ActCatalog          actCatalog;
    Bestiary            bestiary;
    CombatSystem        combatSystem;
    std::unique_ptr<Player> player;

    // --- Étapes du jeu ---

    // Initialisation : charge les CSV, crée le joueur
    void init();

    // Demande le nom du joueur
    void askPlayerName();

    // Boucle de jeu principale
    void gameLoop();

    // Lance un combat contre un monstre aléatoire
    void runRandomCombat();

    // Gère le résultat d'un combat
    void handleCombatResult(CombatResult result, const Monster& monster);

    // Déclenche la fin de partie
    void triggerEnding();

    // Affiche l'écran entre deux combats
    void showInterlude();
};